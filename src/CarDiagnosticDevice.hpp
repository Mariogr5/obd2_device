#include <string>
#include "bluetooth.hpp"
#include "localization.hpp"
#include <sstream>


#ifndef ELM327commands_hpp
#define ELM327commands_hpp

#define CAR_SPEED "010D"
#define CAR_RPM   "010C"
#define FUEL_LEVEL "012F"

class TelemetryDevice
{
    private:
    int car_id;

    struct car_datas
    {
        int car_speed;
        float car_rpm;
        bool if_drive;
        bool if_idling;
        bool if_car_run;
        float fuel_level;
        float odometer;
        bool if_car_errors;
        double geographic_latitude;
        double geographic_longitude; 

    };

    public:

    car_datas diagnostic_datas;

    TelemetryDevice(int Car_id);

    void setup();
    void setup_test();
    void task(int delay_time);
    void task_test(int delay_time);
    void send_command(String command);
    void send_init_command();
    String receive_datas();
    String receive_datas_test();
    int decode_PID_car_speed(String frame);
    float decode_PID_car_rpm(String frame);
    bool check_if_car_running(int car_rpm);
    bool check_if_car_driving(int car_speed);
    bool check_if_car_idling(int car_rpm);
    float decode_PID_car_fuel_level(String frame);

};

#endif