#include "Arduino.h"
#include <cstdarg>

#define SERIAL_STR_MAX_LEN 256

namespace usb
{
  /// @brief Initialises the USB serial output
  void Init();
  /// @brief Formatted printing to the USB serial output
  /// @param format The formatted string
  /// @param ... The format matches
  void Print(char *message, ...);
}