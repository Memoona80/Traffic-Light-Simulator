# 🚦 Street Light Simulator with Pedestrian Detection

An Arduino-based traffic light simulation for a crossroad.  
When a pedestrian is detected via IR sensor, both North-South and East-West lights turn red until the pedestrian passes.

---

## 📹 Demo Video
[link here](https://drive.google.com/file/d/1aG3iC6KdkSaBq32REgLYbd1t_BCRorRq/view?usp=drive_link)

---

## 🛠 Components Used
- Arduino UNO (powered via 5V)
- 6 LEDs (Red, Yellow, Green × 2 sides)
- IR sensor module
- Jumper wires
- Breadboard

---

## 📜 How It Works
1. The system cycles through standard traffic light sequences for NS and EW roads.
2. If the IR sensor detects a pedestrian (pencil used in testing), both directions turn red.
3. Once the pedestrian leaves, normal light sequence resumes.

---

## 💻 Arduino Code
```cpp
// Paste your code here for quick reference
