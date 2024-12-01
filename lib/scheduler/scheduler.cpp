#include "scheduler.h"

unsigned int Scheduler::WaitPeriodFromRate(unsigned int hz)
{
  return (1000000/hz);
}

Scheduler::Scheduler(unsigned int hz)
{
  next_run_time_us_ = MAX_ULONG;
  wait_period_ = Scheduler::WaitPeriodFromRate(hz);
}

void Scheduler::SetRate(unsigned int hz)
{
  wait_period_ = Scheduler::WaitPeriodFromRate(hz);
}

bool Scheduler::ShouldRun()
{
  unsigned long time_now = micros();
  if (time_now < next_run_time_us_)
  {
    return false;
  }

  if (time_now > (next_run_time_us_ + wait_period_))
  {
    next_run_time_us_ = time_now + wait_period_;
    return true;
  }

  next_run_time_us_ += wait_period_;
  return true;
}

void Scheduler::Start()
{
  next_run_time_us_ = micros();
}

void Scheduler::Stop()
{
  next_run_time_us_ = MAX_ULONG;
}