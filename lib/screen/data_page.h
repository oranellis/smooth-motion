#pragma once

#include <memory>

#include "screen.h"

namespace sm {
class IDataPage {
 public:
  virtual void DrawPage(std::shared_ptr<OledScreen> screen) = 0;
};
}  // namespace sm