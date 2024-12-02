#include "usb.h"

void sm::Usb::Init(unsigned long baud)
{
  Serial.begin(baud);
  String init_msg = "Welcome to smooth-motion";
  Serial.println(init_msg.c_str());
}


void sm::Usb::Log(char *format, ...)
{
  char print_cstr[SERIAL_STR_MAX_LEN];
  va_list args;
  va_start(args, format);
  vsnprintf(print_cstr, SERIAL_STR_MAX_LEN, format, args);
  va_end(args);
  Serial.println(print_cstr);
}