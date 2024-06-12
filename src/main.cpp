#include <Arduino.h>
//#include "..\Submodules\esp32-BrokerMQTT\MqttHandler.hpp"
#include "MqttHandler.hpp"
#include "CarDiagnosticDevice.hpp"

	//links2004/WebSockets@^2.4.1
  //bblanchon/ArduinoJson@^7.0.4
  //mikalhart/TinyGPSPlus@^1.0.3
  //knolleary/PubSubClient@^2.8



#define test

TelemetryDevice _device = TelemetryDevice(1);
MqttHandler mqttHandler("topic","Galaxy A71316C", "ufmp4568", "192.168.56.1", "mqtt_user", "ad");
uint8_t device_address[6] = {0xAA, 0xBB, 0xCC, 0x11,0x22, 0x33};



void task()
{
  if(check_connection())
  {
    
    _device.task(2); //Measure Delay


    Serial.println(_device.diagnostic_datas.car_speed);
    delay(1);
    Serial.println(_device.diagnostic_datas.car_rpm);
    delay(1);
    Serial.println(_device.diagnostic_datas.geographic_latitude);
    delay(1);
    Serial.println(_device.diagnostic_datas.geographic_longitude);
    delay(1);
    mqttHandler.handle(_device.diagnostic_datas.car_speed, _device.diagnostic_datas.geographic_latitude, _device.diagnostic_datas.geographic_longitude, "Nord",
    _device.diagnostic_datas.if_idling, _device.diagnostic_datas.if_drive, _device.diagnostic_datas.if_car_run, _device.diagnostic_datas.fuel_level);
    delay(1);

  }
  else
  { 
      bool connected =  SerialBT.connect(device_address);
      Serial.println(connected);
      if(connected)
      {
        Serial.println("Connected");
        delay(2000);
        _device.send_init_command();
      }
      else
      {
        Serial.println("Not connected");
      }
   }

}

void task_test()
{
  if(check_connection())
  {
    
    _device.task_test(2); //Measure Delay

    Serial.println("Car speed: " + String(_device.diagnostic_datas.car_speed));
    delay(1);
    Serial.println("Car RPM: " + String(_device.diagnostic_datas.car_rpm));
    delay(1);
    Serial.println("Fuel Level: " + String(_device.diagnostic_datas.fuel_level));
    delay(1);
    Serial.println("Car latitude: " + String(_device.diagnostic_datas.geographic_latitude));
    delay(1);
    Serial.println("Car longitude: " + String(_device.diagnostic_datas.geographic_longitude));
    delay(1);
    Serial.println("Idling: " + String(_device.diagnostic_datas.if_idling));
    delay(1);
    Serial.println("Drive: " + String(_device.diagnostic_datas.if_drive));
    delay(1);
    Serial.println("Run: " + String(_device.diagnostic_datas.if_car_run));
    delay(1);
    // mqttHandler.handle(_device.diagnostic_datas.car_speed, _device.diagnostic_datas.geographic_latitude, _device.diagnostic_datas.geographic_longitude, "Nord",
    // _device.diagnostic_datas.if_idling, _device.diagnostic_datas.if_drive, _device.diagnostic_datas.if_car_run, _device.diagnostic_datas.fuel_level);
    delay(1);

  }
}


void setup() {
  #ifdef test
  _device.setup_test();
  //mqttHandler.begin();
  #endif
  #ifndef test
  _device.setup()
  #endif
  Serial.begin(115200);
  //mqttHandler.begin();
}

void loop() 
{
  #ifdef test
  task_test();
  #endif

  #ifndef test
  task();
  #endif
}







// if(check_connection())
//   {
    
//     _device.task(2); //Measure Delay
    
//     String speed_message = "Car speed " + String(_device.diagnostic_datas.car_speed);
//     String rpm_message = "Car rpm " + String(_device.diagnostic_datas.car_rpm);
//     String fuel_level = "Car Fuel " + String(_device.diagnostic_datas.fuel_level);
//     String geographic_latitude = "Car geographic latitude " + String(_device.diagnostic_datas.geographic_latitude);
//     String geographic_longitude = "Car geographic longitude " + String(_device.diagnostic_datas.geographic_longitude);

//     Serial.println(speed_message);
//     delay(1);
//     Serial.println(rpm_message);
//     delay(1);
//     Serial.println(geographic_latitude);
//     delay(1);
//     Serial.println(geographic_longitude);
//     //mqttHandler.handle();
//     delay(1);

//   }
//   else
//   { 
//       //SerialBT.connect("AA::BB::CC::11::22::33");
//       bool connected =  SerialBT.connect(device_address);
//       // SerialBT.setPin(pin);
//       Serial.println(connected);
//       if(connected)
//       {
//         Serial.println("Connected");
//         delay(2000);
//         _device.send_init_command();
//       }
//       else
//       {
//         Serial.println("Not connected");
//       }
//       //Serial.println("Dupa");
//       //SerialBT.connect("OBDII");
//       //Serial.println("Connected");
//    }