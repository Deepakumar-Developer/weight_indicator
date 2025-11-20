# 💡 Smart Weight Indicator for Cottage Industry 💡

## Project Overview

This project was developed as a consultancy solution to address a crucial bottleneck in a local cottage food industry (bun production). The goal was to simplify the process of measuring flour portions, significantly improving worker efficiency and accuracy, especially among uneducated labor.

## 1. The Problem: Inconsistent Measurements

The industry struggled with labor delays because workers lacked the training or tools to consistently cut the correct grams of flour for each bun.

* **Issue:** Lack of precision in manual weighing/cutting.
* **Result:** High variance in bun size, leading to wasted time correcting portions, and significant delay in meeting minimum daily production targets (kilograms).

## 2. The Solution: Light-Based Weight Indication

I designed and implemented a custom, low-cost weighing system utilizing visual feedback.

### **Core Features:**

1.  **Visual Guidance:** A three-color LED system (Green, Yellow, Red) immediately informs the worker if the weight is correct, too high, or too low relative to a defined target.
2.  **Target Weight:** Currently hardcoded to **$100 \text{ grams}$** (for demonstration).
3.  **Connectivity:** Included a Bluetooth module for future proofing and remote configuration.

### **Efficiency Impact**

By providing instant, non-numerical feedback, the system drastically reduced the time spent on measuring and correcting flour portions, directly improving labor throughput.

---

## 3. Technical Implementation Details

### A. Hardware Used

| Component | Purpose | Connection Details |
| :--- | :--- | :--- |
| **Microcontroller** | Arduino Nano | Handles processing and logic. |
| **Weight Sensor** | Load Cell | Measures the physical weight. |
| **Amplifier** | HX711 Module | Amplifies and digitizes the load cell signal. |
| **Indicator** | 3 x LEDs (Green, Yellow, Red) | Visual feedback to the user. |
| **Connectivity** | HC-05 Bluetooth Module | Allows remote adjustment of the `constantWeight` variable. |

### B. Pin Mapping

| Component Pin | Arduino Pin | Variable Name |
| :--- | :--- | :--- |
| HX711 (DOUT) | D4 | `LOADCELL_DOUT_PIN` |
| HX711 (SCK) | D5 | `LOADCELL_SCK_PIN` |
| Green LED | D12 | `green_pin` |
| Yellow LED | D11 | `yellow_pin` |
| Red LED | D13 | `red_pin` |

### C. Code Logic (Weight Conditionals)

The core logic uses threshold values to control the LEDs based on the instantaneous weight reading (`float weight`).

| Condition | LED Status | Logic in Code |
| :--- | :--- | :--- |
| **Perfect** | **🟢 Green** | `weight` is within `constantWeight` $\pm$ `DiffValue` |
| **Low** | **🟡 Yellow** | `weight` is within $(C-D)$ to $(C-(D+U))$ |
| **High** | **🔴 Red** | `weight` is within $(C+D)$ to $(C+(D+U))$ |

* **Key Constants:**
    * `constantWeight = 100` (grams)
    * `DiffValue = 2` (The tolerance for the Green zone: $\pm 2g$)
    * `UptoValue = 10` (The threshold beyond which LED is activated)

---

## 4. Next Steps / Future Enhancements

* Develop a simple mobile app to utilize the Bluetooth module and allow staff to remotely set the **`constantWeight`** (target weight) for different bun types.
* Implement a rolling average calculation for stability instead of a fixed average of 10 readings.