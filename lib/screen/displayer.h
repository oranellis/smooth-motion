#pragma once

#include <memory>

#include "data_page.h"
#include "screen.h"

namespace sm {
class Displayer {
 private:
  IDataPage *data_page_;
  std::shared_ptr<OledScreen> screen_;

 public:
  Displayer();
  void Display();
  void InitAndSplash(const char *splash_text);
  void SetDataPage(IDataPage &data_page);
};
}  // namespace sm