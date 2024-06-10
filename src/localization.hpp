
#include <TinyGPS++.h>

#ifndef localization_hpp
#define localization_hpp

#define RXD2 16
#define TXD2 17

struct localization_coordinates
{
    double geographic_X;
    double geographic_Y;
};

void setup_gps_module();

void track_localization();

void get_coordinates();
double get_geographic_longitude();
double get_geographic_latitude();

#endif