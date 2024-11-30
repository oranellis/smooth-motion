#include "screen.h"

void Screen::Init(char *text)
{
  display_ = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE);
  display_->begin();
  display_->clearBuffer();
  display_->setFont(splash_font_);
  display_->drawStr(0, 40, text);
  display_->sendBuffer();
}

void Screen::Coords(sensor::NavPvt *pvt)
{
  unsigned short y_pos = normal_font_ascent_;
  display_->clearBuffer();
  PrintLine(&y_pos, "lat: %d", pvt->lat);
  PrintLine(&y_pos, "lon: %d", pvt->lon);
  PrintLine(&y_pos, "alt: %d", pvt->height_msl);
  PrintLine(&y_pos, "sats: %d, ac: %d", pvt->num_sv, pvt->hor_acc);
  PrintLine(&y_pos, "time: %d:%d:%d", pvt->hour, pvt->minute, pvt->second);
  display_->sendBuffer();
}

void Screen::ImuAccel(sensor::ImuData *imu_data)
{
  unsigned short y_pos = normal_font_ascent_;
  display_->clearBuffer();
  PrintLine(&y_pos, "x: %0.4f", imu_data->accel_x);
  PrintLine(&y_pos, "y: %0.4f", imu_data->accel_y);
  PrintLine(&y_pos, "z: %0.4f", imu_data->accel_z);
  float a_mag = sqrt(sq(imu_data->accel_x) + sq(imu_data->accel_y) + sq(imu_data->accel_z)) / 9.81f;
  PrintLine(&y_pos, "Mag: %0.4fg", a_mag);
  display_->sendBuffer();
}

void Screen::ImuGyro(sensor::ImuData * imu_data)
{
    unsigned short y_pos = normal_font_ascent_;
    display_->clearBuffer();
    PrintLine(&y_pos, "x: %d", imu_data->gyro_x);
    PrintLine(&y_pos, "y: %d", imu_data->gyro_y);
    PrintLine(&y_pos, "y: %d", imu_data->gyro_z);
    display_->sendBuffer();
}

void Screen::PrintLine(unsigned short * y_pos, const char* format, ...)
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

void Screen::PrintLine(unsigned short y_pos, const char* format, ...)
{
    char disp_cstr[STR_MAX_LEN];
    va_list args;
    va_start(args, format);
    vsnprintf(disp_cstr, STR_MAX_LEN, format, args);
    va_end(args);
    display_->setFont(normal_font_);
    display_->drawStr(0, y_pos, disp_cstr);
}