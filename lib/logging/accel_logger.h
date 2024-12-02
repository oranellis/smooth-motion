#pragma once

#include "imu_data.h"
#include "usb.h"

namespace sm
{
  class AccelLogger
  {
  private:
    std::shared_ptr<sm::Usb> usb_;
    std::shared_ptr<sm::sensor::ImuData> imu_data_;

  public:
    AccelLogger(std::shared_ptr<sm::Usb> usb, std::shared_ptr<sm::sensor::ImuData> imu_data);
    void LogAccel();
  };
}