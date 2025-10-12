# EMG-Gesture-Control
Electromyography (EMG) Based Gesture Control: Developed an Arduino-based system to read EMG signals, process voltage levels, and control multiple devices (light, fan, buzzer) based on muscle activity, demonstrating ADC, signal processing, and real-time control logic.

# Electromyography (EMG) Based Gesture Control (Multi-Device)

This project uses an EMG sensor to detect muscle activity and control multiple devices such as lights, fans, and buzzers based on the voltage level of the muscle signal.  
It demonstrates signal acquisition, threshold-based decision-making, and real-time control of multiple outputs.

---

## Project Overview
- **Input:** EMG sensor signal connected to Arduino's analog pin
- **Processing:** Arduino reads the analog voltage, converts it to a digital value, and compares it with predefined thresholds
- **Output:** Multiple devices are controlled via digital output pins (ON/OFF)

---

## Components Used
- Arduino Uno / Nano
- EMG Sensor Module
- Relay Module / LEDs / Motors (for output)
- Jumper wires, breadboard
- Power supply

---

## Features
✅ Real-time muscle signal acquisition  
✅ Multi-level threshold detection  
✅ Control of **multiple devices** (Light, Fan, Buzzer)  
✅ Serial monitoring for debugging  
✅ Modular and scalable design  

---

## Skills Demonstrated
- Embedded C Programming
- ADC (Analog-to-Digital Conversion)
- Signal Processing (Thresholding)
- Multi-Device Control Logic
- Serial Communication for Debugging

---

## Circuit Overview

- EMG Sensor → Arduino A0  
- Device 1 (Light) → Digital Pin 3  
- Device 2 (Fan) → Digital Pin 4  
- Device 3 (Buzzer) → Digital Pin 5  

---

## Source Code

See [(https://github.com/MEENAJASMINE26/EMG-Gesture-Control/blob/main/Electromyography_based_gesture_control.ino)]

---

## Future Improvements
- Implement signal filtering to reduce noise  
- Add gesture classification for multiple muscle movements  
- Replace delay() with millis() for non-blocking control  
- Interface with wireless modules (Bluetooth/WiFi) for remote device control  
- Add LCD/OLED display to show real-time voltage and device status  

---
