#include "task.h"

void sm::Task::SetTaskFunction(std::function<void()> func)
{
  func_ = func;
}

void sm::Task::RunTask()
{
  if (func_)
  {
    func_();
  }
}