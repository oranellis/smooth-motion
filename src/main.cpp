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

  sm::Led led;
  sm::Usb usb(std::make_unique<sm::Scheduler>());

  std::shared_ptr<sm::sensor::Imu> imu = \
    std::make_shared<sm::sensor::Imu>(std::make_unique<sm::Scheduler>());
  std::shared_ptr<sm::sensor::Gps> gps = \
    std::make_shared<sm::sensor::Gps>(std::make_unique<sm::Scheduler>());

  sm::AccelDataPage accel_data_page(imu);
  sm::GpsDataPage gps_data_page(gps);

  sm::Displayer displayer(std::make_unique<sm::Scheduler>(), gps_data_page);

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