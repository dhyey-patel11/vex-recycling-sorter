# VEX Recycling Sorter

Autonomous VEX IQ recycling sorter that feeds, conveys, and classifies bottle caps (plastic vs. metal) using distance sensing + optical reflectivity. Designed for safe, predictable operation with single-cap processing, pause/resume emergency stop, and automatic shutdown after inactivity. Achieved >80% sorting/loading accuracy in testing.  [oai_citation:0‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:1‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

## Demo
- 🎥 Video: (add link here)
- 📸 Photos: (add 2–4 photos here)

---

## Problem
Manual or inconsistent sorting reduces recycling efficiency. This project demonstrates an assembly-line style approach (feeding → conveying → sorting) using VEX IQ hardware and sensor-driven automation.  [oai_citation:2‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:3‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## Key Features
- **Autonomous workflow:** robot remains idle until caps are detected, then runs the full load/sort cycle  [oai_citation:4‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- **Single-cap processing:** only one cap on the conveyor at a time to reduce jams and improve sensor reliability  [oai_citation:5‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:6‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- **Reflectivity-based classification:** plastic vs. metal sorted using optical sensor reflectivity readings  [oai_citation:7‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- **Pause/Resume E-Stop:** Brain button pauses all motors instantly and resumes from the exact point in the cycle (timing-safe)  [oai_citation:8‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:9‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- **Auto shutdown:** if no caps are detected for 30 seconds, robot shuts down to prevent unnecessary motion  [oai_citation:10‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:11‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## System Overview (Mechanical)
The design follows an assembly-line layout with three stages: **feeding, conveying, sorting**. Major subsystems include a gravity-based feed track, wheel feeder, conveyor belt, and a swing-arm diverter to route caps into bins.  [oai_citation:12‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

### Optical Sensor Mounting (Ambient Light Mitigation)
The optical sensor is mounted vertically ~30 mm above the belt with a small “umbrella” shade to reduce ambient light effects and improve repeatability across environments.  [oai_citation:13‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

### Sorting Arm
A pivoting swing-arm guides caps into bins by rotating to different angles depending on detected material, then returns to a calibrated home position each cycle.  [oai_citation:14‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:15‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## Software Overview
The program is modular and organized around reliable startup conditions, cap detection, classification, sorting actuation, safety behavior, and shutdown logic. Startup includes initializing sensors, zeroing motor positions, turning on the optical sensor LED, and ensuring predictable initial state.  [oai_citation:16‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

### Design Choices That Improved Reliability
- **Peak brightness classification:** rather than using a single reflectivity reading, the program samples brightness while the cap is under the sensor and uses the peak value to classify plastic vs. metal (more robust to angle/motion variability).  [oai_citation:17‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- **Timing + pause correctness:** pause state tracks elapsed paused time and subtracts it from cycle timing so the conveyor still receives the intended “real movement time.”  [oai_citation:18‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:19‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## Sensors & Actuators
**Sensors used (as constrained by the project):**
- Optical sensor (reflectivity/brightness)
- Distance sensor (cap presence)
- Encoders
- Brain button (E-Stop)
 [oai_citation:20‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

**Actuators:**
- Feeder motor (loads caps)
- Conveyor motor (moves caps through sensing/sorting)
- Sorting arm motor (diverts cap to the correct bin)

---

## Verification & Testing
Key integration checks included:
- Sorting arm reaches correct angles and returns to 0°
- E-Stop pauses immediately and resumes seamlessly across stages
- Full cycle validation: wait → load → scan → sort → reset → shutdown after inactivity
 [oai_citation:21‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:22‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

**Results:** sorting and loading accuracies **upwards of 80%**, meeting the target threshold established for the final demo.  [oai_citation:23‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc) [oai_citation:24‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## How to Run (VEXcode IQ)
1. Open the project in **VEXcode IQ (C++)**
2. Connect the VEX Brain to your computer
3. Download and run the program on the Brain
4. Load bottle caps into the feeder container
5. Robot will remain idle until a cap is detected, then process one cap per cycle  [oai_citation:25‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

> Note: motor speeds were tuned to account for optical sensor delay (caps moving too fast reduced measurement stability).  [oai_citation:26‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## Project Notes / Lessons Learned
- Mechanical testing + sensor calibration took more time than expected; earlier integration reduces end-stage crunch.  [oai_citation:27‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)
- Two major constraints discovered through testing were **sensor delay vs. motor speed** and **ambient light sensitivity**, solved via speed tuning and a physical shade on the optical sensor.  [oai_citation:28‡Final Report Put Together.pdf](sediment://file_000000003b1c722f8e63d8dcc3a224bc)

---

## Credits
Built as a team project using VEX IQ hardware. (Add team member names/roles if you want.)
