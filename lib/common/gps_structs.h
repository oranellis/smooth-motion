#pragma once

namespace sensor
{
  struct NavPvt
  {
    unsigned char cls;
    unsigned char id;
    unsigned short len;
    unsigned long i_tow; // GPS time of week of the navigation epoch (ms)

    unsigned short year;	 // Year (UTC)
    unsigned char month;	 // Month, range 1..12 (UTC)
    unsigned char day;		 // Day of month, range 1..31 (UTC)
    unsigned char hour;		 // Hour of day, range 0..23 (UTC)
    unsigned char minute;	 // Minute of hour, range 0..59 (UTC)
    unsigned char second;	 // Seconds of minute, range 0..60 (UTC)
    char valid;				 // Validity Flags (see graphic below)
    unsigned long time_acc;	 // Time accuracy estimate (UTC) (ns)
    long nano;				 // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
    unsigned char fix_type;	 // GNSSfix Type, range 0..5
    char flags;				 // Fix Status Flags
    unsigned char reserved1; // reserved
    unsigned char num_sv;	 // Number of satellites used in Nav Solution

    long lon;			   // Longitude (deg)
    long lat;			   // Latitude (deg)
    long height;		   // Height above Ellipsoid (mm)
    long height_msl;	   // Height above mean sea level (mm)
    unsigned long hor_acc; // Horizontal Accuracy Estimate (mm)
    unsigned long ver_acc; // Vertical Accuracy Estimate (mm)

    long vel_n;				   // NED north velocity (mm/s)
    long vel_e;				   // NED east velocity (mm/s)
    long vel_d;				   // NED down velocity (mm/s)
    long gnd_speed;			   // Ground Speed (2-D) (mm/s)
    long heading;			   // Heading of motion 2-D (deg)
    unsigned long s_acc;	   // Speed Accuracy Estimate
    unsigned long heading_acc; // Heading Accuracy Estimate
    unsigned short p_dop;	   // Position dilution of precision
    short reserved2;		   // Reserved
    unsigned long reserved3;   // Reserved
    unsigned char dummy[8];
  };
}