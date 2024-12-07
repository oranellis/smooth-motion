#pragma once

#include <cstdarg>
#include <memory>

#include "Arduino.h"

#define SERIAL_STR_MAX_LEN 256

namespace sm {
class Usb {
 public:
  Usb() = default;
  inline static std::shared_ptr<sm::Usb> CreateSharedPtr() {
    return std::make_shared<sm::Usb>();
  }
  /// @brief Initialises the USB serial output
  void Init(unsigned long baud);
  /// @brief Formatted printing to the USB serial output
  /// @param format The formatted string
  /// @param ... The format matches
  void Log(const char *message, ...);
};
}  // namespace sm
