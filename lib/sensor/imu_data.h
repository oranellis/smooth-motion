#pragma once

#include <memory>

#define IMU_I2C_ADDR 0x68

namespace sm::sensor {
struct ImuData {
  float accel_x = 0;
  float accel_y = 0;
  float accel_z = 0;

  float gyro_x = 0;
  float gyro_y = 0;
  float gyro_z = 0;

  float mag_x = 0;
  float mag_y = 0;
  float mag_z = 0;

  float temp = 0;

  inline static std::shared_ptr<sm::sensor::ImuData> CreateSharedPtr() {
    return std::make_shared<sm::sensor::ImuData>();
  }
};
}  // namespace sm::sensor