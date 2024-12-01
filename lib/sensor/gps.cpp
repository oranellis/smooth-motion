// Code by Karl Hartmann from https://github.com/karl03/gps-speedo

#include "gps.h"

void sensor::Gps::CalcChecksum(unsigned char *CK, NavPvt pvt)
{
  memset(CK, 0, 2);
  for (int i = 0; i < (int)sizeof(NavPvt); i++)
  {
    CK[0] += ((unsigned char *)(&pvt))[i];
    CK[1] += CK[0];
  }
}

bool sensor::Gps::Process()
{
  static int readPosition = 0;
  static unsigned char checksum[2];
  const int payloadSize = sizeof(NavPvt);

  while (GPS_SERIAL.available())
  {
    byte c = GPS_SERIAL.read();
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
        ((unsigned char *)(&pvt_))[readPosition - 2] = c;

      readPosition++;

      if (readPosition == (payloadSize + 2))
      {
        sensor::Gps::CalcChecksum(checksum, pvt_);
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

sensor::Gps::Gps(std::unique_ptr<Scheduler> scheduler)
{
  scheduler_ = std::move(scheduler);
}

sensor::NavPvt sensor::Gps::GetNavPvt()
{
  return pvt_;
}

void sensor::Gps::Init()
{
  GPS_SERIAL.begin(9600);
  for (unsigned int i = 0; i < sizeof(UBLOX_INIT); i++)
  {
    GPS_SERIAL.write(pgm_read_byte(UBLOX_INIT + i));
    // delay(5); // simulating a 38400baud pace (or less), otherwise commands are not accepted by the device.
  }
  GPS_SERIAL.end();
  GPS_SERIAL.begin(115200);
  scheduler_->Start();
}

void sensor::Gps::ScheduledRun()
{
  if (scheduler_->ShouldRun())
  {
    this->Process();
  }
}