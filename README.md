# Rocket-Motor-Thrust-Test-Stand
A rocket motor thrust test stand for commercial and experimental motors. 

Specification:
- Supports up to 45mm in diameter (potentially more tbh)
- Supports up to 200mm in length, but can be expanded
- Physical arming switch
- up to 80 Hz binary telemetry (as high as HX711 can be)
- Physical arming switch
- Software arming
- Heartbeat + link-loss auto-disarm
- Single-shot ignition pulse

## CAD:

<img width="757" height="600" alt="Screenshot 2025-12-14 at 8 37 51 PM" src="https://github.com/user-attachments/assets/ecd83b07-f405-4f2c-8b1a-a97d3d267dba" />

## BOM:

2020 aluminium extrusion lengths:
- 2x 210mm
- 2x 110mm
- 1x 140mm
- 1x 20mm (for mounting load cell)

(optional, only needed for a dual orientation build)
- 2x 100mm
- 1x 150mm
- 2x 30mm

Electronics:
- ESP32
- HX711 + Loadcell (10kg or 20kg)
- IRLZ44N MOSFET
- Switch
- LEDs

Power can be supplied through a power bank or a combination of Li-ion cells with a buck-boost converter/LDO. 
