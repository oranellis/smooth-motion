#include <gps.h>
#include <usb.h>
#include <led.h>
#include <screen.h>
#include <imu.h>
#include <circular_buffer.h>

Screen screen;
U8G2 *disp;
Led led;
sensor::NavPvt pvt{};
sensor::Imu imu;
sensor::ImuData imu_data;
sensor::ImuData imu_data_average;
CircularBuffer<sensor::ImuData, 256> imu_data_buffer;
/* long */ timer_hw_t time; /* ago I can still remember how the music used to make me smile */

void setup()
{
  screen.Init("Smooth Motion");
  led.Colour(0, 255, 0, 1);
  led.On();
  delay(300);
  sensor::GpsInit();
  usb::Init();
  imu.Init(IMU_I2C_ADDR);
  led.Colour(255, 255, 255, 1);
}

void loop()
{
  sensor::GpsProcess(&pvt);
  imu_data = imu.ReadData();
  imu_data_buffer.AddToArray(imu_data);
  imu_data_average = imu_data_buffer.GetBufferAverage();
  screen.ImuAccel(&imu_data_average);
}