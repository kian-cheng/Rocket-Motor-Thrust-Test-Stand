#include <WiFi.h>
#include "HX711.h"

#define AP_SSID "IGNITION_TEST"
#define AP_PASS "fireee"

#define TCP_PORT 3333

#define HX711_DOUT 5
#define HX711_SCK  18
#define IGNITION_PIN   21
#define ARM_SWITCH_PIN 19   // physical arming switch 

WiFiServer server(TCP_PORT);
WiFiClient client;
HX711 scale;

bool softwareArmed = false;
bool ignitionActive = false;

unsigned long lastHeartbeat = 0;
unsigned long ignitionStart = 0;

const unsigned long HEARTBEAT_TIMEOUT = 1500;  // ms
const unsigned long IGNITION_PULSE_MS = 2000;   // ms
const unsigned long TELEMETRY_PERIOD  = 12;    // ~80 Hz

unsigned long lastTelemetry = 0;

//packet structure
struct TelemetryPacket {
  uint8_t  version;
  uint32_t time_ms;
  float    force;
  uint8_t  hw_armed;
  uint8_t  sw_armed;
  uint8_t  ignition;
  int8_t   rssi;
};

void setup() {
  Serial.begin(115200);

  pinMode(IGNITION_PIN, OUTPUT);
  digitalWrite(IGNITION_PIN, LOW);   // FAIL SAFE

  pinMode(ARM_SWITCH_PIN, INPUT_PULLUP);

  scale.begin(HX711_DOUT, HX711_SCK);
  scale.set_scale();   // calibrate later
  scale.tare();

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  handleClient();
  handleHeartbeatTimeout();
  handleIgnitionPulse();
  sendTelemetry();
}

void handleClient() {
  if (!client || !client.connected()) {
    client = server.available();
    return;
  }

  while (client.available()) {
    String cmd = client.readStringUntil('\n');
    cmd.trim();

    if (cmd == "HB") {
      lastHeartbeat = millis();
    }

    else if (cmd == "ARM") {
      softwareArmed = true;
    }

    else if (cmd == "DISARM") {
      softwareArmed = false;
      ignitionActive = false;
      digitalWrite(IGNITION_PIN, LOW);
    }

    else if (cmd == "FIRE") {
      if (ignitionAllowed() && !ignitionActive) {
        ignitionActive = true;
        ignitionStart = millis();
        digitalWrite(IGNITION_PIN, HIGH);
      }
    }
  }
}

bool ignitionAllowed() {
  bool hwArmed = digitalRead(ARM_SWITCH_PIN) == LOW;
  return hwArmed && softwareArmed;
}

void handleHeartbeatTimeout() {
  if (millis() - lastHeartbeat > HEARTBEAT_TIMEOUT) {
    softwareArmed = false;
  }
}

void handleIgnitionPulse() {
  if (ignitionActive && millis() - ignitionStart >= IGNITION_PULSE_MS) {
    ignitionActive = false;
    digitalWrite(IGNITION_PIN, LOW);
  }
}

void sendTelemetry() {
  if (!client || !client.connected()) return;
  if (millis() - lastTelemetry < TELEMETRY_PERIOD) return;

  lastTelemetry = millis();

  TelemetryPacket pkt;
  pkt.version  = 1;
  pkt.time_ms  = millis();
  pkt.force    = scale.get_units(1);
  pkt.hw_armed = digitalRead(ARM_SWITCH_PIN) == LOW;
  pkt.sw_armed = softwareArmed;
  pkt.ignition = ignitionActive;
  pkt.rssi     = WiFi.RSSI();

  client.write((uint8_t*)&pkt, sizeof(pkt));
}

