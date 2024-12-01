#pragma once

#include <Arduino.h>

#define MAX_ULONG 18446744073709551615

class Scheduler
{
  private:
  unsigned int wait_period_;
  unsigned long next_run_time_us_;
  static unsigned int WaitPeriodFromRate(unsigned int hz);

  public:
  Scheduler(unsigned int hz);
  void SetRate(unsigned int hz);
  bool ShouldRun();
  void Start();
  void Stop();
};
