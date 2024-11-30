#pragma once

#define IMU_I2C_ADDR 0x68

namespace sensor
{
  struct ImuData
  {
    float accel_x;
    float accel_y;
    float accel_z;

    float gyro_x;
    float gyro_y;
    float gyro_z;

    float mag_x;
    float mag_y;
    float mag_z;

    float temp;

    ImuData& operator+=(const ImuData& rhs);
    friend ImuData operator+(ImuData lhs, const ImuData& rhs)
    {
        lhs += rhs;
        return lhs;
    }
    ImuData& operator*=(const float rhs);
    friend ImuData operator*(ImuData lhs, const float rhs)
    {
        lhs *= rhs;
        return lhs;
    }
  };
}