#pragma once

#include "task.h"

#include <functional>

namespace sm
{
  class FastTask : public sm::Task
  {
  public:
    FastTask(std::function<void()> func);
  };
}