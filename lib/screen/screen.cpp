#include "screen.h"

void sm::OledScreen::Clear()
{
  display_->clearBuffer();
}

void sm::OledScreen::Init(const char * text)
{
  display_ = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
  display_->begin();
  display_->clearBuffer();
  display_->setFont(OledScreen::splash_font_);
  display_->drawStr(0, 40, text);
  display_->sendBuffer();
  display_->setFont(normal_font_);
}

void sm::OledScreen::PrintLine(unsigned short * y_pos, const char* format, ...)
{
    char disp_cstr[STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(disp_cstr, STR_MAX_LEN, format, args);
    va_end(args);
    display_->drawStr(0, *y_pos, disp_cstr);
    *y_pos += normal_font_height_;
}

void sm::OledScreen::PrintLine(unsigned short y_pos, const char* format, ...)
{
    char disp_cstr[STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(disp_cstr, STR_MAX_LEN, format, args);
    va_end(args);
    display_->drawStr(0, y_pos, disp_cstr);
}

void sm::OledScreen::Render()
{
  display_->sendBuffer();
}