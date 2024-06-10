#include "localization.hpp"


HardwareSerial neogps(1);
TinyGPSPlus gps;

static localization_coordinates _coordinates;

void setup_gps_module()
{
    neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}


void track_localization()
    {

        boolean newData = false;
        for (unsigned long start = millis(); millis() - start < 1000;)
        {
          while (neogps.available())
          {
            if (gps.encode(neogps.read()))
            {
              newData = true;
            }
          }
        }

        if(newData == true)
        {
          newData = false;
          get_coordinates();
        }
        else
        {
            _coordinates.geographic_X = 0;
            _coordinates.geographic_Y = 0;
        }
    }

    void get_coordinates()
    {
        if (gps.location.isValid() == 1)
        {
            Serial.println(gps.location.lat());
            Serial.println(gps.location.lng());
            _coordinates.geographic_X = gps.location.lat();
            _coordinates.geographic_Y = gps.location.lng();

        }
        else
        {
            _coordinates.geographic_X = 0;
            _coordinates.geographic_Y = 0;
        }
    }

    double get_geographic_longitude()
    {
        return _coordinates.geographic_Y;
    }
     double get_geographic_latitude()
    {
        return _coordinates.geographic_X;
    }