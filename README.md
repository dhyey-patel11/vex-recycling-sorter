# VEX Recycling Sorter

Autonomous VEX IQ recycling sorter that feeds, conveys, and classifies bottle caps (plastic vs. metal) using distance sensing + optical reflectivity. Designed for safe, predictable operation with single-cap processing, pause/resume emergency stop, and automatic shutdown after inactivity. Achieved >80% sorting/loading accuracy in testing.

## Demo
- 🎥 Video: [YouTube Demo](https://youtu.be/PbLOYYTk2Z4)
- 📸 Photos: [Images](media/images)

## Problem
Manual or inconsistent sorting reduces recycling efficiency. This project demonstrates an assembly-line style approach (feeding → conveying → sorting) using VEX IQ hardware and sensor-driven automation.

## Key Features
- **Autonomous workflow:** robot remains idle until caps are detected, then runs the full load/sort cycle
- **Single-cap processing:** only one cap on the conveyor at a time to reduce jams and improve sensor reliability
- **Reflectivity-based classification:** plastic vs. metal sorted using optical sensor reflectivity readings
- **Pause/Resume E-Stop:** Brain button pauses all motors instantly and resumes from the exact point in the cycle (timing-safe)
- **Auto shutdown:** if no caps are detected for 30 seconds, robot shuts down to prevent unnecessary motion

## System Overview

### Mechanical
Assembly-line layout with three stages: **feeding, conveying, sorting**. Major subsystems include a gravity-based feed track, wheel feeder, conveyor belt, and a swing-arm diverter to route caps into bins.

### Optical Sensor Mounting (Ambient Light Mitigation)
The optical sensor is mounted vertically ~30 mm above the belt with a small “umbrella” shade to reduce ambient light effects and improve repeatability across environments.

### Sorting Arm
A pivoting swing-arm guides caps into bins by rotating to different angles depending on detected material, then returns to a calibrated home position each cycle.

## Software Overview
Modular control logic organized around reliable startup conditions, cap detection, classification, sorting actuation, safety behavior, and shutdown logic. Startup initializes sensors, zeroes motor positions, turns on the optical sensor LED, and ensures a predictable initial state.

### Design Choices That Improved Reliability
- **Peak brightness classification:** samples brightness while the cap is under the sensor and uses the peak value to classify plastic vs. metal (more robust to angle/motion variability).
- **Timing + pause correctness:** pause state tracks elapsed paused time and subtracts it from cycle timing so the conveyor still receives the intended “real movement time.”

## Sensors & Actuators

### Sensors
- Optical sensor (reflectivity/brightness)
- Distance sensor (cap presence)
- Encoders
- Brain button (E-Stop)

### Actuators
- Feeder motor (loads caps)
- Conveyor motor (moves caps through sensing/sorting)
- Sorting arm motor (diverts cap to the correct bin)

## Verification & Testing
Key integration checks included:
- Sorting arm reaches correct angles and returns to 0°
- E-Stop pauses immediately and resumes seamlessly across stages
- Full cycle validation: wait → load → scan → sort → reset → shutdown after inactivity

**Results:** sorting and loading accuracies **upwards of 80%**, meeting the target threshold established for the final demo.

## How to Run (VEXcode IQ)
1. Open the project in **VEXcode IQ (C++)**
2. Connect the VEX Brain to your computer
3. Download and run the program on the Brain
4. Load bottle caps into the feeder container
5. Robot will remain idle until a cap is detected, then process one cap per cycle

> Note: motor speeds were tuned to account for optical sensor delay (caps moving too fast reduced measurement stability).

## Lessons Learned
- Mechanical testing + sensor calibration took more time than expected; earlier integration reduces end-stage crunch.
- Two major constraints discovered through testing were **sensor delay vs. motor speed** and **ambient light sensitivity**, solved via speed tuning and a physical shade on the optical sensor.

## Credits
Built as a team project using VEX IQ hardware.
