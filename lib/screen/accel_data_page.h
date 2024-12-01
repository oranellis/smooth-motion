#pragma once

#include "data_page.h"
#include "imu.h"
#include "screen.h"

class AccelDataPage : public IDataPage
{
  private:
  std::shared_ptr<sensor::Imu> imu_;

  public:
  AccelDataPage(std::shared_ptr<sensor::Imu> imu);
  void DrawPage(std::shared_ptr<OledScreen> screen) override;
};