#pragma once

#include "screen.h"

class IDataPage
{
  public:
  virtual void DrawPage(std::shared_ptr<OledScreen> screen) = 0;
};