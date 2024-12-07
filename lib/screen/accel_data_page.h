#pragma once

#include <memory>

#include "data_page.h"
#include "imu_data.h"
#include "screen.h"

namespace sm {
class AccelDataPage : public IDataPage {
 private:
  std::shared_ptr<sm::sensor::ImuData> imu_data_;

 public:
  AccelDataPage(std::shared_ptr<sm::sensor::ImuData> imu_data);
  void DrawPage(std::shared_ptr<OledScreen> screen) override;
};
}  // namespace sm
