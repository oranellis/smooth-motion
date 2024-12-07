#include "rate_task.h"

unsigned int sm::RateTask::WaitPeriodFromRate(float hz) {
  return static_cast<unsigned int>(1000000 / hz);
}

sm::RateTask::RateTask(std::function<void()> func, float rate_hz)
    : wait_period_(sm::RateTask::WaitPeriodFromRate(rate_hz)),
      next_run_time_us_(0) {
  this->SetTaskFunction(func);
}

void sm::RateTask::SetNextRunTime(unsigned long run_time_us) {
  next_run_time_us_ = run_time_us;
}

void sm::RateTask::SetRate(float rate_hz) {
  wait_period_ = RateTask::WaitPeriodFromRate(rate_hz);
}

bool sm::RateTask::ShouldRun(unsigned long time_now) {
  if (time_now < next_run_time_us_) {
    return false;
  }

  if (time_now > (next_run_time_us_ + wait_period_)) {
    next_run_time_us_ = time_now + wait_period_;
    return true;
  }

  next_run_time_us_ += wait_period_;
  return true;
}
