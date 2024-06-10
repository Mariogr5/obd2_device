#include "BluetoothSerial.h"
#include <string>
#include "gpio.hpp"

#ifndef bluetooth_hpp
#define bluetooth_hpp

    extern BluetoothSerial SerialBT;

    void setup_bluetooth(int id);
    
    void send_bluetooth_command(String PID);
    String receive_bluetooth_datas();
    bool check_connection();

#endif
