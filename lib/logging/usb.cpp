#include "usb.h"

sm::Usb::Usb(std::unique_ptr<sm::Scheduler> scheduler) : scheduler_(std::move(scheduler))
{
}

void sm::Usb::Init()
{
  Serial.begin(9600);
  String init_msg = "Welcome to smooth-motion";
  Serial.println(init_msg.c_str());
}

void sm::Usb::ScheduledLog(char *format, ...)
{
  if (scheduler_->ShouldRun())
  {
    char print_cstr[SERIAL_STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(print_cstr, SERIAL_STR_MAX_LEN, format, args);
    va_end(args);
    Serial.println(print_cstr);
  }
}