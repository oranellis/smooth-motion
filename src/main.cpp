#include "accel_data_page.h"
#include "gps_data_page.h"
#include "displayer.h"
#include "gps.h"
#include "imu.h"
#include "led.h"
#include "scheduler.h"
#include "usb.h"

#include <memory>

int main()
{
  init(); // Arduino initialisation, required

  Led led;
  Usb usb(std::make_unique<Scheduler>(1));

  std::shared_ptr<sensor::Imu> imu = \
    std::make_shared<sensor::Imu>(std::make_unique<Scheduler>(4000));
  std::shared_ptr<sensor::Gps> gps = \
    std::make_shared<sensor::Gps>(std::make_unique<Scheduler>(10));

  AccelDataPage accel_data_page(imu);
  GpsDataPage gps_data_page(gps);

  Displayer displayer(std::make_unique<Scheduler>(60), gps_data_page);

  led.Colour(0, 255, 0, 1);
  led.On();
  usb.Init();
  displayer.InitAndSplash((char *)"Smooth Motion");
  gps->Init();
  imu->Init(IMU_I2C_ADDR);
  led.Colour(255, 255, 255, 1);
  displayer.Start();

  while (true)
  {
    gps->ScheduledRun();
    imu->ScheduledRun();
    displayer.ScheduledRun();
  }
}