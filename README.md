# Smooth Motion

A EKF based motion tracker using a GPS and IMU. Built using the Wavemotion RP2040-Zero, an Adafruit 128x64 OLED screen, a pimoroni ICM20948, and a BN220 GPS.

## Development

- [x] Set up platformio environment and build system on VSCode
- [x] Set up compile\_commands.json and other files for error highlighting and autocomplete in Nvim
- [x] Get W2812B led on the RP2040-Zero working with the FastLED lib
- [x] Import and test GPS code from Karl's gps-speedo project
- [x] Set up u8g2 lib for displaying text on the OLED screen
- [x] Set up the Adafruit ICM20X lib for reading GPS data
- [x] Create data displays for the GPS and IMU data
- [x] Create a command loop (interrupt-less scheduler) for running repeating tasks
- [x] Test loop times with different modules and discover the display takes Aaaaages to run (~40ms per frame)
- [ ] Create data abstractions for the sensor data and make the state variables
- [ ] Design the observation model for the IMU and GPS measurements
- [ ] Design the state transition model for the IMU and GPS measurements
- [ ] Select a lightweight linear algebra library
- [ ] Implement a basic KF (or UKF) using said library
- [ ] Experiment with the process and observation noise covariance matrices
