#include "screen.h"

void OledScreen::Clear()
{
  display_->clearBuffer();
}

void OledScreen::Init(const char * text)
{
  display_ = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
  display_->begin();
  display_->clearBuffer();
  display_->setFont(splash_font_);
  display_->drawStr(0, 40, text);
  display_->sendBuffer();
}

void OledScreen::PrintLine(unsigned short * y_pos, const char* format, ...)
{
    char disp_cstr[STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(disp_cstr, STR_MAX_LEN, format, args);
    va_end(args);
    display_->setFont(normal_font_);
    display_->drawStr(0, *y_pos, disp_cstr);
    *y_pos += normal_font_height_;
}

void OledScreen::PrintLine(unsigned short y_pos, const char* format, ...)
{
    char disp_cstr[STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(disp_cstr, STR_MAX_LEN, format, args);
    va_end(args);
    display_->setFont(normal_font_);
    display_->drawStr(0, y_pos, disp_cstr);
}

void OledScreen::Render()
{
  display_->sendBuffer();
}

// void OledScreen::Coords(sensor::NavPvt *pvt)
// {
//   unsigned short y_pos = normal_font_ascent_;
//   display_->clearBuffer();
//   PrintLine(&y_pos, "lat: %d", pvt->lat);
//   PrintLine(&y_pos, "lon: %d", pvt->lon);
//   PrintLine(&y_pos, "alt: %d", pvt->height_msl);
//   PrintLine(&y_pos, "sats: %d, ac: %d", pvt->num_sv, pvt->hor_acc);
//   PrintLine(&y_pos, "time: %d:%d:%d", pvt->hour, pvt->minute, pvt->second);
//   display_->sendBuffer();
// }