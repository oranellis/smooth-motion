#include "scheduler.h"

unsigned int sm::Scheduler::WaitPeriodFromRate(unsigned int hz)
{
  return (1000000/hz);
}

sm::Scheduler::Scheduler()
  : next_run_time_us_(MAX_ULONG),
    wait_period_(sm::Scheduler::WaitPeriodFromRate(1))
{
}

sm::Scheduler::~Scheduler() = default;

void sm::Scheduler::SetRate(unsigned int hz)
{
  wait_period_ = sm::Scheduler::WaitPeriodFromRate(hz);
}

bool sm::Scheduler::ShouldRun()
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

void sm::Scheduler::Start()
{
  next_run_time_us_ = micros();
}

void sm::Scheduler::Stop()
{
  next_run_time_us_ = MAX_ULONG;
}