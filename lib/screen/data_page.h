#pragma once

#include "screen.h"

#include <memory>

namespace sm
{
  class IDataPage
  {
  public:
    virtual void DrawPage(std::shared_ptr<OledScreen> screen) = 0;
  };
}