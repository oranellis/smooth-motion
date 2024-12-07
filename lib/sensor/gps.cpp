// Code by Karl Hartmann from https://github.com/karl03/gps-speedo

#include "gps.h"

sm::sensor::Gps::Gps(std::shared_ptr<sm::sensor::NavPvt> nav_pvt)
    : nav_pvt_(nav_pvt) {}

void sm::sensor::Gps::CalcChecksum(unsigned char *CK, sm::sensor::NavPvt pvt) {
  memset(CK, 0, 2);
  for (int i = 0; i < (int)sizeof(sm::sensor::NavPvt); i++) {
    CK[0] += ((unsigned char *)(&pvt))[i];
    CK[1] += CK[0];
  }
}

void sm::sensor::Gps::InitSerial() {
  GPS_SERIAL.begin(9600);
  for (unsigned int i = 0; i < sizeof(UBLOX_INIT); i++) {
    GPS_SERIAL.write(pgm_read_byte(UBLOX_INIT + i));
    delay(5);  // simulating a 38400baud pace (or less), otherwise commands are
               // not accepted by the device.
  }
  GPS_SERIAL.end();
  GPS_SERIAL.begin(115200);
}

void sm::sensor::Gps::ReadData() {
  static int readPosition = 0;
  static unsigned char checksum[2];
  const int payloadSize = sizeof(sm::sensor::NavPvt);

  while (GPS_SERIAL.available()) {
    byte c = GPS_SERIAL.read();
    if (readPosition < 2) {
      if (c == UBX_HEADER[readPosition])
        readPosition++;
      else
        readPosition = 0;
    } else {
      if ((readPosition - 2) < payloadSize)
        ((unsigned char *)(&pvt_temp_))[readPosition - 2] = c;

      readPosition++;

      if (readPosition == (payloadSize + 2)) {
        sm::sensor::Gps::CalcChecksum(checksum, pvt_temp_);
      } else if (readPosition == (payloadSize + 3)) {
        if (c != checksum[0]) readPosition = 0;
      } else if (readPosition == (payloadSize + 4)) {
        readPosition = 0;
        if (c == checksum[1]) {
          *nav_pvt_ = pvt_temp_;
        }
      } else if (readPosition > (payloadSize + 4)) {
        readPosition = 0;
      }
    }
  }
  return;
}
