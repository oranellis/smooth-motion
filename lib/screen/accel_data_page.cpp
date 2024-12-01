#include "accel_data_page.h"

AccelDataPage::AccelDataPage(std::shared_ptr<sensor::Imu> imu)
  : imu_(imu)
{}

void AccelDataPage::DrawPage(std::shared_ptr<OledScreen> screen)
{
  unsigned short y_pos = OledScreen::normal_font_ascent_;
  std::shared_ptr<sensor::ImuData> imu_data = imu_->GetData();
  float average_accel = imu_->GetAverageAccel();
  screen->Clear();
  screen->PrintLine(&y_pos, "x: %0.4f", imu_data->accel_x);
  screen->PrintLine(&y_pos, "y: %0.4f", imu_data->accel_y);
  screen->PrintLine(&y_pos, "z: %0.4f", imu_data->accel_z);
  screen->PrintLine(&y_pos, "Mag: %0.4fg", average_accel / 9.81f);
  screen->Render();
}