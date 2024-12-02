#pragma once

#include "fast_task.h"
#include "rate_task.h"

#include <Arduino.h>

#include <vector>

#define MAX_ULONG 18446744073709551615

namespace sm
{
  class Scheduler
  {
  private:
    std::vector<FastTask> fast_tasks_;
    std::vector<RateTask> rate_tasks_;

    Scheduler() = default;
    ~Scheduler() = default;
    Scheduler(const Scheduler &) = delete;
    Scheduler &operator=(const Scheduler &) = delete;

  public:
    static Scheduler &GetScheduler()
    {
      static Scheduler instance; // Guaranteed to be initialized only once
      return instance;
    }
    void AddTask(FastTask fast_task);
    void AddTask(RateTask rate_task);
    void RunSchedule();
  };
}