#pragma once

#include "imu_structs.h"
#include "scheduler.h"

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define IMU_I2C_ADDR 0x68

namespace sensor
{
  class Imu
  {
  private:
    Adafruit_ICM20948 icm_;
    sensors_event_t accel_;
    sensors_event_t gyro_;
    sensors_event_t mag_;
    sensors_event_t temp_;

  public:
    void Init(unsigned char i2c_addr);
    sensor::ImuData ReadData();
  };
}