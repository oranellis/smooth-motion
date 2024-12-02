#include "scheduler.h"

void sm::Scheduler::AddTask(sm::FastTask fast_task)
{
  fast_tasks_.push_back(fast_task);
}

void sm::Scheduler::AddTask(sm::RateTask rate_task)
{
  rate_tasks_.push_back(rate_task);
}

void sm::Scheduler::RunSchedule()
{
  unsigned long time_now;
  for (auto fast_task = fast_tasks_.begin(); fast_task != fast_tasks_.end(); ++fast_task)
  {
    fast_task->RunTask();
  }

  for (auto rate_task = rate_tasks_.begin(); rate_task != rate_tasks_.end(); ++rate_task)
  {
    time_now = micros();
    if (rate_task->ShouldRun(time_now))
    {
      rate_task->RunTask();
    }
  }
}