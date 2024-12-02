#include "imu.h"

sm::sensor::Imu::Imu(std::shared_ptr<sm::sensor::ImuData> imu_data)
  : imu_data_(imu_data)
{}

void sm::sensor::Imu::InitI2c(unsigned char addr)
{
  if (!icm_.begin_I2C(addr))
  {
    Serial.println("Failed to find ICM20948"); // replace with logger interface
    while (true)                               // Trap and halt execution
    {
      delay(1000);
    }
  }
  Serial.println("Found ICM20948 sensor");
  Serial.print("Accelerometer range set to: ");
  switch (icm_.getAccelRange())
  {
  case ICM20948_ACCEL_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case ICM20948_ACCEL_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case ICM20948_ACCEL_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case ICM20948_ACCEL_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  Serial.println("OK");

  // icm_.setGyroRange(ICM20948_GYRO_RANGE_2000_DPS);
  Serial.print("Gyro range set to: ");
  switch (icm_.getGyroRange())
  {
  case ICM20948_GYRO_RANGE_250_DPS:
    Serial.println("250 degrees/s");
    break;
  case ICM20948_GYRO_RANGE_500_DPS:
    Serial.println("500 degrees/s");
    break;
  case ICM20948_GYRO_RANGE_1000_DPS:
    Serial.println("1000 degrees/s");
    break;
  case ICM20948_GYRO_RANGE_2000_DPS:
    Serial.println("2000 degrees/s");
    break;
  }

  //  icm_.setAccelRateDivisor(4095);
  uint16_t accel_divisor = icm_.getAccelRateDivisor();
  float accel_rate = 1125 / (1.0 + accel_divisor);

  Serial.print("Accelerometer data rate divisor set to: ");
  Serial.println(accel_divisor);
  Serial.print("Accelerometer data rate (Hz) is approximately: ");
  Serial.println(accel_rate);

  //  icm_.setGyroRateDivisor(255);
  uint8_t gyro_divisor = icm_.getGyroRateDivisor();
  float gyro_rate = 1100 / (1.0 + gyro_divisor);

  Serial.print("Gyro data rate divisor set to: ");
  Serial.println(gyro_divisor);
  Serial.print("Gyro data rate (Hz) is approximately: ");
  Serial.println(gyro_rate);

  // icm_.setMagDataRate(AK09916_MAG_DATARATE_10_HZ);
  Serial.print("Magnetometer data rate set to: ");
  switch (icm_.getMagDataRate())
  {
  case AK09916_MAG_DATARATE_SHUTDOWN:
    Serial.println("Shutdown");
    break;
  case AK09916_MAG_DATARATE_SINGLE:
    Serial.println("Single/One shot");
    break;
  case AK09916_MAG_DATARATE_10_HZ:
    Serial.println("10 Hz");
    break;
  case AK09916_MAG_DATARATE_20_HZ:
    Serial.println("20 Hz");
    break;
  case AK09916_MAG_DATARATE_50_HZ:
    Serial.println("50 Hz");
    break;
  case AK09916_MAG_DATARATE_100_HZ:
    Serial.println("100 Hz");
    break;
  }
}

std::shared_ptr<sm::sensor::ImuData> sm::sensor::Imu::GetData()
{
  return imu_data_;
}

float sm::sensor::Imu::GetAverageAccel()
{
  return accel_hist;
}

void sm::sensor::Imu::ReadData()
{
  icm_.getEvent(&accel_, &gyro_, &temp_, &mag_);

  char print_cstr[64];
  snprintf(print_cstr, 64, "x: %0.3f, y: %0.3f, z: %0.3f", accel_.acceleration.x, accel_.acceleration.y, accel_.acceleration.z);
  Serial.println(print_cstr);

  imu_data_->accel_x = accel_.acceleration.x;
  imu_data_->accel_y = accel_.acceleration.y;
  imu_data_->accel_z = accel_.acceleration.z;

  imu_data_->gyro_x = gyro_.gyro.x;
  imu_data_->gyro_y = gyro_.gyro.y;
  imu_data_->gyro_z = gyro_.gyro.z;

  imu_data_->mag_x = mag_.magnetic.x;
  imu_data_->mag_y = mag_.magnetic.y;
  imu_data_->mag_z = mag_.magnetic.z;

  imu_data_->temp = temp_.temperature;

  float new_accel = sqrt( \
    sq(accel_.acceleration.x) + \
    sq(accel_.acceleration.y) + \
    sq(accel_.acceleration.z));
  
  accel_hist = (accel_hist * HIST_BIAS) + (new_accel * (1.0f - HIST_BIAS));
}