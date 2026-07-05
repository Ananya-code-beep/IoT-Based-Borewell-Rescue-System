# Borewell Rescue System using IoT

An ESP32-based robotic rescue system designed to safely extract individuals — especially children — trapped in deep, narrow borewells. The system combines a motorized descent/lifting mechanism, a servo-controlled gripper, an ultrasonic depth sensor, and remote monitoring/control through the Blynk IoT platform.

> Major project — B.E. Computer Science Engineering (Internet of Things, Cyber Security Including Blockchain Technology), Visvesvaraya Technological University, Belagavi.
> Yenepoya Institute of Technology, Moodbidri, Mangalore — 2025–2026.

## Team

| Name | USN |
|---|---|
| Ananya Raj K | 4DM22IC011 |
| Aneena Dileep | 4DM22IC012 |
| Mohammad Fairoz | 4DM22IC033 |
| Mohammed Razi Abdul Rasheed | 4DM22IC037 |

**Guide:** Ms. Rachana P, Assistant Professor, Dept. of CSE (IoT, CS including BT)

## Problem Statement

Traditional borewell rescue operations rely on digging a parallel pit next to the borewell — a slow, labor-intensive process that risks soil collapse, offers no real-time visibility into the victim's condition, and often takes hours or even days. This project proposes a faster, safer, technology-driven alternative.

## How It Works

1. An ESP32 microcontroller acts as the central controller, coordinating motors, sensors, and communication.
2. The unit is lowered into the borewell using a 12V geared DC motor (winch), driven through an L298N motor driver.
3. An ultrasonic sensor continuously measures depth and detects obstacles as the unit descends.
4. A stepper motor (28BYJ-48 + ULN2003 driver) provides fine rotational alignment near the victim.
5. A servo-driven gripper closes gently around the victim once aligned.
6. The victim is lifted back to the surface at a slow, controlled speed.
7. Throughout the process, the operator monitors depth, motor status, and system state in real time via the Blynk mobile app, and status LEDs (Red/Yellow/Green) indicate error, in-progress, and complete states.

## System Architecture

```
Operator (Blynk App)
        │
        ▼
  Blynk Cloud (IoT Platform)
        │
        ▼
  ESP32 Microcontroller  ──────┐
        │                      │
        ▼                      ▼
  Motor Drivers          Ultrasonic Sensor
 (L298N / ULN2003)         (depth/obstacle)
        │
        ▼
 DC Motors / Servo / Stepper / Status LEDs
```

Full architecture diagrams, data flow, sequence, use case, and ER diagrams are included in the project report under `docs/`.

## Hardware Components

| Component | Purpose |
|---|---|
| ESP32 Dev Module | Central controller, Wi-Fi/Blynk connectivity |
| Arduino UNO R3 | Secondary controller / sensor interfacing |
| 12V Geared DC Motor (x2) | Vertical winch movement |
| L298N Motor Driver | Dual H-bridge control for DC motors |
| MG996R Servo Motor | Gripper open/close mechanism |
| 28BYJ-48 Stepper Motor | Fine rotational alignment / extraction |
| ULN2003 Driver | Stepper motor driver |
| HC-SR04 Ultrasonic Sensor | Depth measurement & obstacle detection |
| 18650 Li-ion Battery Pack | Portable power supply |
| LEDs (Red/Yellow/Green) | Status indication |
| Breadboard + Jumper Wires | Prototyping connections |

## Software / Libraries

- Arduino IDE
- ESP32 Board Package
- `Servo.h`
- `Stepper.h`
- `BlynkSimpleEsp32.h`
- Blynk IoT mobile app (dashboard with motor, servo, stepper controls and live depth/status display)

## Repository Structure

```
├── firmware/
│   ├── borewell_rescue_esp32.ino   # Main ESP32 firmware
│   └── secrets.h.example           # Template for WiFi/Blynk credentials
├── images/                         # Prototype photos
├── docs/                           # Project report reference
├── LICENSE
└── README.md
```

## Getting Started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and add the ESP32 board package.
2. Install the required libraries: `Blynk`, `Servo`, `Stepper` (via Library Manager).
3. Copy `firmware/secrets.h.example` to `firmware/secrets.h` and fill in your WiFi and Blynk credentials (this file is git-ignored so your credentials stay private).
4. Wire the components according to the pin mapping defined at the top of `borewell_rescue_esp32.ino`.
5. Set up a Blynk template with virtual pins V0–V10 (motor control, servo, stepper, LEDs, and depth display) as described in the report.
6. Upload the firmware to the ESP32 and power on the system.

## Results

The prototype successfully demonstrated:
- Smooth, controlled vertical descent and ascent
- Accurate real-time depth readings via the ultrasonic sensor
- Reliable gripper actuation for secure, gentle holding
- Stable Blynk-based remote monitoring and control
- Consistent operation across repeated test cycles

Prototype photos are available in the [`images/`](./images) folder.

## Future Improvements

- Integration of a live camera feed for direct visual monitoring
- Environmental sensors (oxygen, gas, temperature) for victim safety monitoring
- AI-assisted alignment and grip-stability detection
- Ruggedized housing for real-world deployment conditions

## License

This project is licensed under the MIT License — see [LICENSE](./LICENSE) for details.

## References

See the full reference list in the project report (`docs/`), covering prior borewell rescue research from 2014–2024.
