#include "accel_data_page.h"

sm::AccelDataPage::AccelDataPage(std::shared_ptr<sm::sensor::ImuData> imu_data)
  : imu_data_(imu_data)
{}

void sm::AccelDataPage::DrawPage(std::shared_ptr<sm::OledScreen> screen)
{
  unsigned short y_pos = sm::OledScreen::normal_font_ascent_;
  screen->Clear();
  screen->PrintLine(&y_pos, "a_x: %0.4f", imu_data_->accel_x);
  screen->PrintLine(&y_pos, "a_y: %0.4f", imu_data_->accel_y);
  screen->PrintLine(&y_pos, "a_z: %0.4f", imu_data_->accel_z);
  float accel_mag = sqrt(sq(imu_data_->accel_x) + sq(imu_data_->accel_y) + sq(imu_data_->accel_z));
  screen->PrintLine(&y_pos, "a_mag: %0.4fg", accel_mag / 9.81f);
  screen->Render();
}