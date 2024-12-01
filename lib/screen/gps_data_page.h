#pragma once

#include "data_page.h"
#include "gps.h"
#include "screen.h"

class GpsDataPage : public IDataPage
{
  private:
  std::shared_ptr<sensor::Gps> gps_;

  public:
  GpsDataPage(std::shared_ptr<sensor::Gps> gps);
  void DrawPage(std::shared_ptr<OledScreen> screen) override;
};