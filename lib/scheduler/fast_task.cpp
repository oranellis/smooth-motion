#include "fast_task.h"

sm::FastTask::FastTask(std::function<void()> func) {
  this->SetTaskFunction(func);
}