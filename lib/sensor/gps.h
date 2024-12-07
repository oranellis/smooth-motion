// Code by Karl Hartmann from https://github.com/karl03/gps-speedo
#pragma once

#include <memory>

#include "Arduino.h"
#include "gps_data.h"

#define GPS_SERIAL Serial1

namespace sm::sensor {
const unsigned char UBLOX_INIT[] PROGMEM = {
    // Disable NMEA
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x00, 0x24,  // GxGGA off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x01, 0x2B,  // GxGLL off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x02, 0x32,  // GxGSA off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x03, 0x39,  // GxGSV off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x04, 0x40,  // GxRMC off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0xF0, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x01, 0x05, 0x47,  // GxVTG off

    // Disable UBX
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x17, 0xDC,  // NAV-PVT off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x12, 0xB9,  // NAV-POSLLH off
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x13, 0xC0,  // NAV-STATUS off

    // Enable UBX
    0xB5, 0x62, 0x06, 0x01, 0x08, 0x00, 0x01, 0x07, 0x00, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x18, 0xE1,  // NAV-PVT on
    // 0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x13,0xBE,
    // //NAV-POSLLH on
    // 0xB5,0x62,0x06,0x01,0x08,0x00,0x01,0x03,0x00,0x01,0x00,0x00,0x00,0x00,0x14,0xC5,
    // //NAV-STATUS on

    // Rate
    0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00,
    0x7A, 0x12,  //(10Hz)
    // 0xB5,0x62,0x06,0x08,0x06,0x00,0xC8,0x00,0x01,0x00,0x01,0x00,0xDE,0x6A,
    // //(5Hz)
    // 0xB5,0x62,0x06,0x08,0x06,0x00,0xE8,0x03,0x01,0x00,0x01,0x00,0x01,0x39
    // //(1Hz)

    // Baud
    // 0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xD0,0x08,0x00,0x00,0x00,0x96,0x00,0x00,
    // 0x23,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xAF,0x70, //38400
    0xB5, 0x62, 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08,
    0x00, 0x00, 0x00, 0xC2, 0x01, 0x00, 0x23, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xDC, 0x5E,  // 115200

    // Navigation Mode
    // 0xB5,0x62,0x06,0x24,0x24,0x00,0xFF,0xFF,0x04,0x03,0x00,0x00,0x00,0x00,0x10,0x27,0x00,0x00,
    // 0x05,0x00,0xFA,0x00,0xFA,0x00,0x64,0x00,0x2C,0x01,0x00,0x00,0x00,0x00,0x10,0x27,0x00,0x00,
    // 0x00,0x00,0x00,0x00,0x00,0x00,0x4B,0x97  // Automotive

    // Save Config
    // 0xB5, 0x62, 0x06, 0x09, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    // 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // 0x17, 0x31, 0xBF // Not working

};

const unsigned char UBX_HEADER[] = {0xB5, 0x62};

class Gps {
 private:
  std::shared_ptr<sm::sensor::NavPvt> nav_pvt_;
  sm::sensor::NavPvt pvt_temp_;
  static void CalcChecksum(unsigned char *CK, sm::sensor::NavPvt pvt);

 public:
  Gps(std::shared_ptr<sm::sensor::NavPvt> nav_pvt);
  ~Gps() = default;
  void InitSerial();
  bool ReadData();
};
}  // namespace sm::sensor