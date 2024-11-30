// Code by Karl Hartmann from https://github.com/karl03/gps-speedo

#include "gps.h"

namespace sensor
{
  void GpsInit()
  {
    Serial1.begin(9600);
    for (unsigned int i = 0; i < sizeof(UBLOX_INIT); i++)
    {
      Serial1.write(pgm_read_byte(UBLOX_INIT + i));
      delay(5); // simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
    }
    Serial1.end();
    Serial1.begin(115200);
  }

  bool GpsProcess(NavPvt *pvt)
  {
    static int readPosition = 0;
    static unsigned char checksum[2];
    const int payloadSize = sizeof(NavPvt);

    while (Serial1.available())
    {
      byte c = Serial1.read();
      if (readPosition < 2)
      {
        if (c == UBX_HEADER[readPosition])
          readPosition++;
        else
          readPosition = 0;
      }
      else
      {
        if ((readPosition - 2) < payloadSize)
          ((unsigned char *)(pvt))[readPosition - 2] = c;

        readPosition++;

        if (readPosition == (payloadSize + 2))
        {
          GpsCalcChecksum(checksum, *pvt);
        }
        else if (readPosition == (payloadSize + 3))
        {
          if (c != checksum[0])
            readPosition = 0;
        }
        else if (readPosition == (payloadSize + 4))
        {
          readPosition = 0;
          if (c == checksum[1])
          {
            return true;
          }
        }
        else if (readPosition > (payloadSize + 4))
        {
          readPosition = 0;
        }
      }
    }
    return false;
  }

  void GpsCalcChecksum(unsigned char *CK, NavPvt pvt)
  {
    memset(CK, 0, 2);
    for (int i = 0; i < (int)sizeof(NavPvt); i++)
    {
      CK[0] += ((unsigned char *)(&pvt))[i];
      CK[1] += CK[0];
    }
  }
}