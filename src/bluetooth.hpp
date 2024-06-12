#include "BluetoothSerial.h"
#include <string>

#ifndef bluetooth_hpp
#define bluetooth_hpp

    extern BluetoothSerial SerialBT;

    void setup_bluetooth(int id);
    void setup_bluetooth_test(int id);

    void send_bluetooth_command(String PID);
    String receive_bluetooth_datas();
    String receive_bluetooth_datas_test();
    bool check_connection();

#endif
