# Animal Deterrent Alarm
### Summary
The Arduino-based pet deterrence device uses an ultrasonic sensor to detect motion within a specified range. When an object comes into the detection range, the device triggers an alarm. The purpose is to deter pets from entering restricted areas, such as kitchen counters or specific rooms.

### Components
- Ultrasonic Sensor (HC-SR04)
- Piezoelectric Buzzer
- LEDs (1 red, 1 green)
- Arduino (Uno, Nano, etc.)
- Battery pack (providing 7-12V)
- 220Ω resistors for LEDs

## Connections
1. Battery Packs:
   - Connect the battery packs in series to provide a total voltage between 7V and 12V.
   - Connect the positive terminal of the battery packs to the Vin pin on the Arduino.
   - Connect the negative terminal of the battery packs to the GND pin on the Arduino.

2. Ultrasonic Sensor:
   - VCC to 5V on Arduino
   - Trig to a digital pin (e.g., D2)
   - Echo to a digital pin (e.g., D3)
   - GND to GND on Arduino

3. Piezoelectric Buzzer:
   - Positive to a digital pin (e.g., D9)
   - Negative to GND on Arduino

4. LEDs:
   - Green LED: Anode (longer leg) to a digital pin (e.g., D4), Cathode (shorter leg) to GND through a 220Ω resistor
   - Red LED: Anode (longer leg) to a digital pin (e.g., D5), Cathode (shorter leg) to GND through a 220Ω resistor

5. Toggle:
   - One side to a digital pin (e.g., D6)
   - Other side to GND on Arduino

### Operations/Routines
1. **Initialization and Calibration:**
    - Power on the device.
    - The ultrasonic sensor initializes.
    - The green LED turns on, indicating the calibration phase.
    - The device measures the initial distance and stores it as a reference.

2. **Detection Cycle:**
    - The device enters a low-power mode to conserve energy.
    - Every 3 seconds, the ultrasonic sensor activates to measure the distance.
    - If the measured distance differs from the initial (calibrated) distance, it implies potential motion or presence within the monitored area.
    - If a difference in distance is detected, the red LED turns on with the green LED, signaling a warning phase.

3. **Alarm Triggering:**
    - The green LED turns off, indicating an alarm.
    - If the detected object doesn't move away within 3 seconds, the buzzer gets activated, producing a sound alarm.
    - The alarm sounds for up to 3 seconds or stops immediately if the object moves away.
    - If the object remains for the entire alarm duration, the device assumes an error (like displacement or an object falling in the path), stops the alarm, and re-calibrates the distance.

4. **Re-calibration and Stabilization:**
    - After an alarm or an error assumption, the device re-calibrates by taking the current distance as the new reference.
    - It then enters a stabilization phase, waiting for 3 seconds to ensure no further disturbances.
    - If stable, the device returns to the low-power detection cycle.

### Notes
- The device uses a piezoelectric buzzer for the alarm, the volume of which can be adjusted in the code.
- The ultrasonic sensor's accuracy can be influenced by environmental factors; regular calibration helps maintain reliability.
- The device is designed to be battery-powered for portability, with power conservation considerations in operation cycles.
