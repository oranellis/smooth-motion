#pragma once

#include <Arduino.h>

#define MAX_ULONG 18446744073709551615

namespace sm
{
  class Scheduler
  {
  private:
    unsigned int wait_period_;
    unsigned long next_run_time_us_;
    static unsigned int WaitPeriodFromRate(unsigned int hz);

    Scheduler();
    ~Scheduler();
    Scheduler(const Scheduler &) = delete;
    Scheduler &operator=(const Scheduler &) = delete;

  public:
    static Scheduler &GetScheduler()
    {
      static Scheduler instance; // Guaranteed to be initialized only once
      return instance;
    }
    void SetRate(unsigned int hz);
    bool ShouldRun();
    void Start();
    void Stop();
  };
}