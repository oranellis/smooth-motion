#pragma once

#include "scheduler.h"

#include "Arduino.h"

#include <cstdarg>

#define SERIAL_STR_MAX_LEN 256

namespace sm
{
  class Usb
  {
  private:
    std::unique_ptr<Scheduler> scheduler_;

  public:
    Usb(std::unique_ptr<Scheduler> scheduler_);
    /// @brief Initialises the USB serial output
    void Init();
    /// @brief Formatted printing to the USB serial output
    /// @param format The formatted string
    /// @param ... The format matches
    void ScheduledLog(char *message, ...);
  };
}