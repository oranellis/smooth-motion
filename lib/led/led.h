#include <FastLED.h>

#define LED_PIN 16
#define COLOUR_ORDER GRB

namespace sm {
class Led {
 public:
  Led();
  ~Led();
  void On();
  void Off();
  void Toggle();
  void Colour(unsigned char r, unsigned char g, unsigned char b,
              unsigned char brightness);

 private:
  unsigned char red_;
  unsigned char green_;
  unsigned char blue_;
  unsigned char brightness_;
  bool state_;
  CRGB leds_[1];
  void UpdateLed();
};
}  // namespace sm
