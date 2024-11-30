#include "led.h"

Led::Led()
{
  red_ = 255; // max 8 bit num
  green_ = 255;
  blue_ = 255;
  brightness_ = 255;
  state_ = false;

  FastLED.addLeds<WS2812, LED_PIN, COLOUR_ORDER>(leds_, 1);
  FastLED.setBrightness(0);
}

Led::~Led()
{
  FastLED.clearData();
}

void Led::On()
{
  state_ = true;
  UpdateLed();
}

void Led::Off()
{
  state_ = false;
  UpdateLed();
}

void Led::Toggle()
{
  state_ = !state_;
  UpdateLed();
}

void Led::Colour(
  unsigned char r,
  unsigned char g,
  unsigned char b,
  unsigned char brightness)
{
  red_ = r;
  green_ = g;
  blue_ = b;
  brightness_ = brightness;
  UpdateLed();
}

void Led::UpdateLed()
{
  if (state_)
  {
    FastLED.setBrightness(brightness_);
  }
  else
  {
    FastLED.setBrightness(0);
  }
  leds_[0] = CRGB(red_, green_, blue_);
  FastLED.show();

}