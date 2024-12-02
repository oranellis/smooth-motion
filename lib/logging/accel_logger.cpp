#include "accel_logger.h"

sm::AccelLogger::AccelLogger(std::shared_ptr<sm::Usb> usb, std::shared_ptr<sm::sensor::ImuData> imu_data)
    : usb_(usb),
      imu_data_(imu_data)
{
}

void sm::AccelLogger::LogAccel()
{
  usb_->Log("x: %0.3f, y: %0.3f, z: %0.3f", imu_data_->accel_x, imu_data_->accel_y, imu_data_->accel_z);
}