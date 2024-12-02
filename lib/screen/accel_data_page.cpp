#include "accel_data_page.h"

sm::AccelDataPage::AccelDataPage(std::shared_ptr<sm::sensor::ImuData> imu_data)
  : imu_data_(imu_data)
{}

void sm::AccelDataPage::DrawPage(std::shared_ptr<sm::OledScreen> screen)
{
  unsigned short y_pos = sm::OledScreen::normal_font_ascent_;
  screen->Clear();
  screen->PrintLine(&y_pos, "x: %0.4f", imu_data_->accel_x);
  screen->PrintLine(&y_pos, "y: %0.4f", imu_data_->accel_y);
  screen->PrintLine(&y_pos, "z: %0.4f", imu_data_->accel_z);
  screen->PrintLine(&y_pos, "Mag: %0.4fg", 1.0f / 9.81f);
  screen->Render();
}