#pragma once

#include "imu_structs.h"
#include "scheduler.h"

#include <Adafruit_ICM20X.h>
#include <Adafruit_ICM20948.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <memory>

#define IMU_I2C_ADDR 0x68
#define HIST_BIAS 0.75f

namespace sensor
{
  class Imu
  {
  private:
    std::unique_ptr<Scheduler> scheduler_;
    Adafruit_ICM20948 icm_;
    sensors_event_t accel_;
    sensors_event_t gyro_;
    sensors_event_t mag_;
    sensors_event_t temp_;
    std::shared_ptr<sensor::ImuData> imu_data_;
    float accel_hist;
    void ReadData();

  public:
    Imu(std::unique_ptr<Scheduler> scheduler);
    std::shared_ptr<sensor::ImuData> GetData();
    float GetAverageAccel();
    void Init(unsigned char i2c_addr);
    void ScheduledRun();
  };
}