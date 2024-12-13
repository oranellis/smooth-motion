#include <Arduino.h>

#include <memory>

#include "accel_data_page.h"
#include "accel_logger.h"
#include "displayer.h"
#include "gps.h"
#include "gps_data_page.h"
#include "imu.h"
#include "led.h"
#include "scheduler.h"
#include "usb.h"

void SwapPages(sm::Displayer &displayer, bool &is_page_1, sm::IDataPage &page1,
               sm::IDataPage &page2) {
  if (is_page_1) {
    is_page_1 = !is_page_1;
    displayer.SetDataPage(page2);
  } else {
    is_page_1 = !is_page_1;
    displayer.SetDataPage(page1);
  }
}

void setup() {
  // LED
  sm::Led led;
  led.Colour(255, 255, 255, 1);
  led.On();

  // Oled Display
  auto displayer = sm::Displayer();
  displayer.InitAndSplash((char *)"Smooth Motion");

  // IMU
  auto imu_data = sm::sensor::ImuData::CreateSharedPtr();
  auto imu = sm::sensor::Imu(imu_data);
  imu.InitI2c(IMU_I2C_ADDR);

  // GPS
  auto nav_pvt = sm::sensor::NavPvt::CreateSharedPtr();
  auto gps = sm::sensor::Gps(nav_pvt);
  gps.InitSerial();

  // USB
  auto usb = sm::Usb::CreateSharedPtr();
  auto accel_logger = sm::AccelLogger(usb, imu_data);
  usb->Init(9600);

  // Data Pages
  bool is_gps_page = false;
  auto accel_data_page = sm::AccelDataPage(imu_data);
  auto gps_data_page = sm::GpsDataPage(nav_pvt);
  displayer.SetDataPage(accel_data_page);

  // Scheduler
  sm::Scheduler &scheduler = sm::Scheduler::GetScheduler();
  scheduler.AddTask(sm::FastTask([&imu]() { imu.ReadData(); }));
  scheduler.AddTask(sm::RateTask([&gps]() { gps.ReadData(); }, 10));
  scheduler.AddTask(sm::RateTask([&displayer]() { displayer.Display(); }, 30));
  // scheduler.AddTask(sm::RateTask(
  //     [&displayer, &is_gps_page, &gps_data_page, &accel_data_page]() {
  //       SwapPages(displayer, is_gps_page, gps_data_page, accel_data_page);
  //     },
  //     0.2));
  // scheduler.AddTask(sm::RateTask([&accel_logger]()
  //                                { accel_logger.LogAccel(); }, 20));
  scheduler.AddTask(
      sm::RateTask([&scheduler, &usb]() { scheduler.LogLoopTime(usb); }, 10));
  scheduler.AddTask(
      sm::RateTask([&scheduler]() { scheduler.ClearMaxLooptime(); }, 0.5));

  // Init Finished
  led.Colour(0, 0, 255, 1);

  // Event Loop
  while (true) {
    scheduler.RunSchedule();
    led.Colour(0, 255, 0, 1);
  }
}

void loop() {/* Unused */}