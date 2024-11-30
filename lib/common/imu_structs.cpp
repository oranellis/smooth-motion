#include "imu_structs.h"

sensor::ImuData& sensor::ImuData::operator+=(const ImuData& rhs)
{
  this->accel_x += rhs.accel_x;
  this->accel_y += rhs.accel_y;
  this->accel_z += rhs.accel_z;

  this->gyro_x += rhs.gyro_x;
  this->gyro_y += rhs.gyro_y;
  this->gyro_z += rhs.gyro_z;

  this->mag_x += rhs.mag_x;
  this->mag_y += rhs.mag_y;
  this->mag_z += rhs.mag_z;

  this->temp += rhs.temp;

  return *this;
}

sensor::ImuData& sensor::ImuData::operator*=(const float rhs)
{

  this->accel_x *= rhs;
  this->accel_y *= rhs;
  this->accel_z *= rhs;

  this->gyro_x *= rhs;
  this->gyro_y *= rhs;
  this->gyro_z *= rhs;

  this->mag_x *= rhs;
  this->mag_y *= rhs;
  this->mag_z *= rhs;

  this->temp *= rhs;

  return *this;
}