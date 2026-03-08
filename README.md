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
<img width="1040" height="877" alt="image" src="https://github.com/user-attachments/assets/6d5b501f-a4cf-4212-bbdd-92d7d6e653af" />


## BOM:

2020 aluminium extrusion lengths:
- 2x 230mm
- 2x 110mm
- 1x 160mm
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
