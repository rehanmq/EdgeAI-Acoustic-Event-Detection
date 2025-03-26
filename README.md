HEAD
# EdgeAI Acoustic Event Detection

This project is an ESP32-based embedded AI system that detects acoustic events like claps, knocks, and alarms in real time.

## 🎯 Features
- Audio capture using INMP441 MEMS microphone
- MFCC feature extraction using Edge Impulse
- TinyML model inference on ESP32
- Output trigger via LED/buzzer

## 💡 Hardware Required
- ESP32 DevKit
- INMP441 Microphone
- LED / Buzzer (optional)
- Breadboard + jumper wires

## 🛠️ Setup Instructions
1. Train your model on [Edge Impulse](https://edgeimpulse.com)
2. Export model as C++ library and place it inside `model/`
3. Flash `main.ino` to your ESP32 using Arduino IDE
4. Observe real-time detection in Serial Monitor

## 🔧 Optional Add-ons
- Relay control for appliances
- BLE alerts to mobile devices
- Solar power module for IoT deployment



---

# EdgeAI-Acoustic-Event-Detection
EdgeAI-powered embedded system using ESP32 and Edge Impulse to detect real-time acoustic events like claps, knocks, and alarms.
 24ac578f60e7321aff60b910ea358334eaf3a4ac
