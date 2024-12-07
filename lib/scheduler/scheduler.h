#pragma once

#include <Arduino.h>

#include <memory>
#include <vector>

#include "circular_buffer.h"
#include "fast_task.h"
#include "rate_task.h"
#include "usb.h"

#define MAX_ULONG 18446744073709551615

namespace sm {
class Scheduler {
 private:
  std::vector<FastTask> fast_tasks_;
  std::vector<RateTask> rate_tasks_;
  sm::CircularBuffer<unsigned int, 100> loop_times_us_;
  unsigned int max_loop_time_us_ = 0;
  unsigned int last_loop_time_us_ =
      0;  // To keep loop timing calculations within the event loop

  Scheduler() = default;
  ~Scheduler() = default;
  Scheduler(const Scheduler &) = delete;
  Scheduler &operator=(const Scheduler &) = delete;

 public:
  static Scheduler &GetScheduler() {
    static Scheduler instance;  // Guaranteed to be initialized only once
    return instance;
  }
  void AddTask(FastTask fast_task);
  void AddTask(RateTask rate_task);
  void ClearMaxLooptime();
  void LogLoopTime(std::shared_ptr<sm::Usb> usb);
  void RunSchedule();
};
}  // namespace sm
