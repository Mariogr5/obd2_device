#include "bluetooth.hpp"

   BluetoothSerial SerialBT;
    //SerialBT.begin("esp_test" + char(id),true);
    void setup_bluetooth(int id) 
    {
        SerialBT.begin("esp_test" + char(id),true);
        SerialBT.setPin("1234");
        //set_gpios_high();
    }

    void setup_bluetooth_test(int id) 
    {
        SerialBT.begin("esp_test" + char(id));
        SerialBT.setPin("1234");
    }

    void send_bluetooth_command(String PID)
    {
        uint8_t buf[PID.length()];

        memcpy(buf,PID.c_str(),PID.length());
        SerialBT.write(buf, PID.length());
        delay(1);
    }

    String receive_bluetooth_datas()
    {
        String message = "";
        uint16_t i = 0;
        while (SerialBT.available()) {
            String part = SerialBT.readStringUntil('\n'); // Odczytanie części wiadomości
            if (part != ">")
                message += part;                      // Dodanie części do bufora
            i++;                           // Zwiększenie licznika części

            //Serial.print("Otrzymano część ");
            //Serial.print(i);
            //Serial.print(": ");
            Serial.println(part);

    // Sprawdzenie, czy odebrano wszystkie 3 części wiadomości
            if (i == 3) {
            //Serial.println("Otrzymano pełną wiadomość:");
            Serial.println(message);
            }
        }
//     //     // while(1)
//     //     // {
//     //     //     delay(1);
//     //     //     i++;
//     //     //     if(SerialBT.available())
//     //     //     {
//     //     //         message = SerialBT.readStringUntil('\r');
//     //     //         //message += SerialBT.readStringUntil('\n');
//     //     //         //message += SerialBT.readStringUntil('\n');
//     //     //         //Serial.println(message);
//     //     //         //if(message == "" || message == "BUS INIT: OK" )
//     //     //          //   continue;
//     //     //         //if (message == ">")
//     //     //         //    return ">";
//     //     //         break;
//     //     //     }
//     //     //     if(i == 300)
//     //     //     {
//     //     //         Serial.println("Nic nie odevrano");
//     //     //         //break;
//     //     //     }

//     //     //     //Serial.println("Nic nie odebrano");

//     //     // }

        if (message != "")
            return message;
        return "00 00";
    }
    

    String receive_bluetooth_datas_test()
    {
        String message = "";
        uint16_t i = 0;
        //while (SerialBT.available()) {
        while(1)
        {
            if(SerialBT.available()){
            message += SerialBT.readStringUntil('\n');
            Serial.println(message);
            break;
            }
        }

        if (message != "")
            return message;
        return "00 00";
    }

    bool check_connection()
    {
        return SerialBT.connected();
    }
