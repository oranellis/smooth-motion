#pragma once

namespace sensor
{
  struct NavPvt
  {
    unsigned char cls = 0;
    unsigned char id = 0;
    unsigned short len = 0;
    unsigned long i_tow = 0; // GPS time of week of the navigation epoch (ms)

    unsigned short year = 0;	 // Year (UTC)
    unsigned char month = 0;	 // Month, range 1..12 (UTC)
    unsigned char day = 0;		 // Day of month, range 1..31 (UTC)
    unsigned char hour = 0;		 // Hour of day, range 0..23 (UTC)
    unsigned char minute = 0;	 // Minute of hour, range 0..59 (UTC)
    unsigned char second = 0;	 // Seconds of minute, range 0..60 (UTC)
    char valid = 0;				 // Validity Flags (see graphic below)
    unsigned long time_acc = 0;	 // Time accuracy estimate (UTC) (ns)
    long nano = 0;				 // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
    unsigned char fix_type = 0;	 // GNSSfix Type, range 0..5
    char flags = 0;				 // Fix Status Flags
    unsigned char reserved1 = 0; // reserved
    unsigned char num_sv = 0;	 // Number of satellites used in Nav Solution

    long lon = 0;			   // Longitude (deg)
    long lat = 0;			   // Latitude (deg)
    long height = 0;		   // Height above Ellipsoid (mm)
    long height_msl = 0;	   // Height above mean sea level (mm)
    unsigned long hor_acc = 0; // Horizontal Accuracy Estimate (mm)
    unsigned long ver_acc = 0; // Vertical Accuracy Estimate (mm)

    long vel_n = 0;				   // NED north velocity (mm/s)
    long vel_e = 0;				   // NED east velocity (mm/s)
    long vel_d = 0;				   // NED down velocity (mm/s)
    long gnd_speed = 0;			   // Ground Speed (2-D) (mm/s)
    long heading = 0;			   // Heading of motion 2-D (deg)
    unsigned long s_acc = 0;	   // Speed Accuracy Estimate
    unsigned long heading_acc = 0; // Heading Accuracy Estimate
    unsigned short p_dop = 0;	   // Position dilution of precision
    short reserved2 = 0;		   // Reserved
    unsigned long reserved3 = 0;   // Reserved
    unsigned char dummy[8];
  };
}