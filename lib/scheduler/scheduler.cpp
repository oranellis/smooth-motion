#include "scheduler.h"

void sm::Scheduler::AddTask(sm::FastTask fast_task)
{
  fast_tasks_.push_back(fast_task);
}

void sm::Scheduler::AddTask(sm::RateTask rate_task)
{
  rate_tasks_.push_back(rate_task);
}

void sm::Scheduler::ClearMaxLooptime()
{
  max_loop_time_us_ = 0;
}

void sm::Scheduler::LogLoopTime(std::shared_ptr<sm::Usb> usb)
{
  unsigned int average_looptime_us = loop_times_us_.GetBufferAverage();
  usb->Log((char*)"t_loop_us: %d, max: %d", average_looptime_us, max_loop_time_us_);
}

void sm::Scheduler::RunSchedule()
{
  // Loop timing calculations
  unsigned long loop_start_time_us = micros();
  loop_times_us_.AddToArray(last_loop_time_us_);
  if (last_loop_time_us_ > max_loop_time_us_)
  {
    max_loop_time_us_ = last_loop_time_us_;
  }

  for (auto fast_task = fast_tasks_.begin(); fast_task != fast_tasks_.end(); ++fast_task)
  {
    fast_task->RunTask();
  }

  for (auto rate_task = rate_tasks_.begin(); rate_task != rate_tasks_.end(); ++rate_task)
  {
    if (rate_task->ShouldRun(micros()))
    {
      rate_task->RunTask();
    }
  }
  last_loop_time_us_ = micros() - loop_start_time_us;
}