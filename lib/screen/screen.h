#include "gps_structs.h"
#include "imu_structs.h"

#include <U8g2lib.h>
#include <Wire.h>

#include <cstdarg>

#define STR_MAX_LEN 64

class Screen
{
public:
  /// @brief Initialises the screen
  /// @param text The startup text to display
  void Init(char *text);
  /// @brief Prints gps coordinates to the screen
  /// @param pvt Pointer to the gps data struct
  void Coords(sensor::NavPvt *pvt);
  /// @brief Prints accelerometer data to the screen
  /// @param imu_data Pointer to the imu data struct
  void ImuAccel(sensor::ImuData *imu_data);
  /// @brief Prints gyroscope data to the screen
  /// @param imu_data Pointer to the imu data struct
  void ImuGyro(sensor::ImuData *imu_data);

private:
  U8G2 *display_;
  const unsigned char *normal_font_ = u8g2_font_profont12_mr;
  const char normal_font_height_ = 12;
  const char normal_font_ascent_ = 8;
  const unsigned char *splash_font_ = u8g2_font_logisoso16_tr;
  float maxaccel_;

  /// @brief Prints a line of text to the screen and increments the y_pos, does not send the buffer
  /// @param y_pos Base line y position for the text, is incrememted by the text height after draw
  /// @param format The text with format specifiers
  /// @param ... The format matches
  void PrintLine(unsigned short *y_pos, const char *format, ...);
  /// @brief Prints a line of text to the screen, does not send the buffer
  /// @param y_pos Base line y position for the text
  /// @param format The text with format specifiers
  /// @param ... The format matches
  void PrintLine(unsigned short y_pos, const char *format, ...);
};