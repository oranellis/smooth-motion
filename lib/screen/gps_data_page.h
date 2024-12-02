#pragma once

#include "data_page.h"
#include "gps.h"
#include "screen.h"

namespace sm
{
  class GpsDataPage : public IDataPage
  {
  private:
    std::shared_ptr<sm::sensor::Gps> gps_;

  public:
    GpsDataPage(std::shared_ptr<sm::sensor::Gps> gps);
    void DrawPage(std::shared_ptr<OledScreen> screen) override;
  };
}