#pragma once

#include <functional>

#include "task.h"

namespace sm {
class FastTask : public sm::Task {
 public:
  FastTask(std::function<void()> func);
};
}  // namespace sm
