#pragma once

#include "data_page.h"
#include "gps_data.h"
#include "screen.h"

namespace sm {
class GpsDataPage : public IDataPage {
 private:
  std::shared_ptr<sm::sensor::NavPvt> nav_pvt_;

 public:
  GpsDataPage(std::shared_ptr<sm::sensor::NavPvt> nav_pvt);
  void DrawPage(std::shared_ptr<OledScreen> screen) override;
};
}  // namespace sm