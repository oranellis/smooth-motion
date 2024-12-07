#pragma once

#include <Adafruit_ICM20948.h>
#include <Adafruit_ICM20X.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <memory>

#include "imu_data.h"

#define IMU_I2C_ADDR 0x68
#define HIST_BIAS 0.75f

namespace sm::sensor {
class Imu {
 private:
  Adafruit_ICM20948 icm_;
  sensors_event_t accel_;
  sensors_event_t gyro_;
  sensors_event_t mag_;
  sensors_event_t temp_;
  std::shared_ptr<sm::sensor::ImuData> imu_data_;
  float accel_hist;

 public:
  Imu(std::shared_ptr<sm::sensor::ImuData> imu_data);
  float GetAverageAccel();
  void InitI2c(unsigned char addr);
  void ReadData();
};
}  // namespace sm::sensor