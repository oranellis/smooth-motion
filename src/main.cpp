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
  sm::Usb usb;

  auto imu_data = sm::sensor::ImuData::CreateSharedPtr();
  sm::sensor::Imu imu{imu_data};
  auto nav_pvt = sm::sensor::NavPvt::CreateSharedPtr();
  sm::sensor::Gps gps{nav_pvt};

  sm::AccelDataPage accel_data_page{imu_data};
  sm::GpsDataPage gps_data_page{nav_pvt};
  sm::Displayer displayer{gps_data_page};

  sm::Scheduler &scheduler = sm::Scheduler::GetScheduler();

  led.Colour(0, 255, 0, 1);
  led.On();
  displayer.InitAndSplash((char *)"Smooth Motion");
  usb.Init();
  gps.InitSerial();
  imu.InitI2c(IMU_I2C_ADDR);
  led.Colour(255, 255, 255, 1);

  auto imu_task = sm::RateTask{[&imu]()
                               { imu.GetData(); }, 400};
  auto gps_task = sm::RateTask{[&gps]()
                               { gps.ReadData(); }, 10};
  auto display_task = sm::RateTask{[&displayer]()
                                   { displayer.Display(); }, 60};

  scheduler.AddTask(imu_task);
  scheduler.AddTask(gps_task);
  scheduler.AddTask(display_task);

  while (true)
  {
    scheduler.RunSchedule();
  }
}