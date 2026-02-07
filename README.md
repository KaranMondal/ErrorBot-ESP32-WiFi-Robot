# ErrorBot-ESP32-WiFi-Robot
# ErrorBot 🤖

**ErrorBot** is a Wi-Fi controlled robot built using **ESP32**, **L298N motor driver**, and **Blynk IoT**, featuring a **hardware safety switch** and an **expressive OLED display**.

The name *ErrorBot* represents a practical engineering approach — adapting and building a reliable system even under hardware constraints.

---

## 🔧 Features
- 📱 Wi-Fi control using Blynk IoT platform
- 🛑 Physical master ON/OFF safety switch (6A 1-way)
- 😊 OLED smiley expressions during idle state
- ⚙️ Stable forward & backward motion
- 🔋 Battery powered motor driver
- 🧠 Safe single-channel motor operation

---

## 🧠 Project Overview
ErrorBot connects to a Wi-Fi network using ESP32 and communicates with the Blynk cloud server.  
Motor commands are sent from the Blynk mobile application and processed by the ESP32 to control the robot via an L298N motor driver.

An OLED display provides real-time visual feedback using expressions and text.  
A physical hardware switch ensures fail-safe operation by overriding software control when needed.

Due to partial motor driver failure, the robot operates in **single-channel mode**, allowing forward and backward motion only.

---

## 📦 Components Used
- ESP32 Devkit V1  
- L298N Motor Driver  
- DC Motors  
- OLED Display (128×64, I2C)  
- 6A 1-Way Mechanical Switch  
- Lithium-ion Batteries & Holder  
- Jumper Wires  
- Battery Charger  

---

## 🖥️ Software & Tools
- Arduino IDE  
- Blynk IoT App  
- ESP32 Board Package  
- Adafruit SSD1306 & GFX Libraries  

---

## ⚙️ Working Principle
1. ESP32 connects to Wi-Fi
2. Blynk app sends control commands
3. ESP32 processes instructions
4. Motor driver moves the robot
5. OLED displays robot state
6. Physical switch overrides all control for safety

---

## 🚀 Applications
- IoT-based robotics
- Smart vehicle prototypes
- Embedded systems education
- Remote-controlled systems

---

## 🔮 Future Scope
- Dual-channel motor control for turning
- Speed control using PWM
- Battery voltage monitoring
- Camera integration
- Autonomous navigation
- Advanced OLED animations

---

## 👨‍💻 Author
**Karan Mondal**

---

## 📜 License
This project is released under the MIT License.
