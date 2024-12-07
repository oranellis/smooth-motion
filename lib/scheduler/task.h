#pragma once

#include <functional>

namespace sm {
class Task {
 private:
  std::function<void()> func_;

 protected:
  void SetTaskFunction(std::function<void()>);

 public:
  void RunTask();
};
}  // namespace sm
