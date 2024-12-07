#pragma once

#include <U8g2lib.h>
#include <Wire.h>

#include <cstdarg>

#define STR_MAX_LEN 64

namespace sm {
class OledScreen {
 private:
  U8G2 *display_;
  float maxaccel_;

 public:
  static constexpr const unsigned char *normal_font_ = u8g2_font_profont12_mr;
  static constexpr const char normal_font_height_ = 12;
  static constexpr const char normal_font_ascent_ = 8;
  static constexpr const unsigned char *splash_font_ = u8g2_font_logisoso16_tr;

  void Clear();
  void Init(const char *text);
  /// @brief Prints a line of text to the screen and increments the y_pos, does
  /// not send the buffer
  /// @param y_pos Base line y position for the text, is incrememted by the text
  /// height after draw
  /// @param format The text with format specifiers
  /// @param ... The format matches
  void PrintLine(unsigned short *y_pos, const char *format, ...);
  /// @brief Prints a line of text to the screen, does not send the buffer
  /// @param y_pos Base line y position for the text
  /// @param format The text with format specifiers
  /// @param ... The format matches
  void PrintLine(unsigned short y_pos, const char *format, ...);
  void Render();
};
}  // namespace sm
