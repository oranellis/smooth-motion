#pragma once

#include "task.h"

#include <functional>

namespace sm
{
  class RateTask : public sm::Task
  {
  private:
    unsigned int wait_period_;
    unsigned long next_run_time_us_;
    static unsigned int WaitPeriodFromRate(float hz);

  public:
    RateTask(std::function<void()> func, float rate_hz);
    void SetNextRunTime(unsigned long run_time_us);
    void SetRate(float rate_hz);
    bool ShouldRun(unsigned long time_now);
  };
}