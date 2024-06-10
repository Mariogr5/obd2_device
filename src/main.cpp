#include <Arduino.h>
#include "gpio.hpp"
//#include "..\Submodules\esp32-BrokerMQTT\MqttHandler.hpp"
#include "CarDiagnosticDevice.hpp"
TelemetryDevice _device = TelemetryDevice(1);
//MqttHandler mqttHandler(ssid, password, mqtt_server, mqtt_user, mqtt_password);
uint8_t device_address[6] = {0xAA, 0xBB, 0xCC, 0x11,0x22, 0x33};

void setup() {
  _device.setup();
  Serial.begin(115200);
  //mqttHandler.begin();
}

void loop() 
{
  if(check_connection())
  {

    _device.task(2); //Measure Delay
    
    String speed_message = "Car speed " + String(_device.diagnostic_datas.car_speed);
    String rpm_message = "Car rpm " + String(_device.diagnostic_datas.car_rpm);
    String fuel_level = "Car Fuel " + String(_device.diagnostic_datas.fuel_level);
    String geographic_latitude = "Car geographic latitude " + String(_device.diagnostic_datas.geographic_latitude);
    String geographic_longitude = "Car geographic longitude " + String(_device.diagnostic_datas.geographic_longitude);

    Serial.println(speed_message);
    delay(1);
    Serial.println(rpm_message);
    delay(1);
    Serial.println(geographic_latitude);
    delay(1);
    Serial.println(geographic_longitude);
    //mqttHandler.handle();
    delay(1);

  }
  else
  { 
      //SerialBT.connect("AA::BB::CC::11::22::33");
      bool connected =  SerialBT.connect(device_address);
      // SerialBT.setPin(pin);
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
      //Serial.println("Dupa");
      //SerialBT.connect("OBDII");
      //Serial.println("Connected");
   }
}
