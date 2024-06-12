#include "CarDiagnosticDevice.hpp"


TelemetryDevice::TelemetryDevice(int Car_id) : car_id(Car_id){}

void TelemetryDevice::setup()
{
    setup_bluetooth(car_id);
    setup_gps_module();
}

void TelemetryDevice::setup_test()
{
    setup_bluetooth_test(car_id);
    setup_gps_module();
}


void TelemetryDevice::send_init_command()
{
    send_command("ATI");
    delay(200);
    Serial.println(receive_datas());
}
void TelemetryDevice:: task(int delay_time)
{
    send_command(CAR_SPEED);
    delay(1000);
    String speed_frame = receive_datas();
    int car_speed = decode_PID_car_speed(speed_frame);

    send_command(CAR_RPM);
    delay(1000);
    String rpm_frame = receive_datas();
    int car_rpm = decode_PID_car_rpm(rpm_frame);

    send_command(FUEL_LEVEL);
    delay(1000);
     String fuel_frame = receive_datas();
     int fuel_level = decode_PID_car_fuel_level(fuel_frame);

    track_localization();

    diagnostic_datas.car_speed = car_speed;
    diagnostic_datas.car_rpm = fuel_level;
    diagnostic_datas.fuel_level = fuel_level;
    diagnostic_datas.if_car_run = check_if_car_running(4);
    diagnostic_datas.if_drive = check_if_car_driving(car_speed);
    diagnostic_datas.if_idling = check_if_car_idling(4);
    diagnostic_datas.geographic_latitude = get_geographic_latitude();
    diagnostic_datas.geographic_longitude = get_geographic_longitude();

}  

void TelemetryDevice:: task_test(int delay_time)
{
    send_command(CAR_SPEED);
    delay(1000);
    // String speed_frame = receive_datas_test();
    int car_speed = decode_PID_car_speed(receive_datas_test());

    send_command(CAR_RPM);
    delay(1000);
    // String rpm_frame = receive_datas_test();
    int car_rpm = decode_PID_car_rpm(receive_datas_test());

    send_command(FUEL_LEVEL);
    delay(1000);
    //  String fuel_frame = receive_datas_test();
     int fuel_level = decode_PID_car_fuel_level(receive_datas_test());

    track_localization();

    Serial.println(car_speed);
    diagnostic_datas.car_speed = car_speed;
    diagnostic_datas.car_rpm = car_rpm;
    diagnostic_datas.fuel_level = fuel_level;
    diagnostic_datas.if_car_run = check_if_car_running(4);
    diagnostic_datas.if_drive = check_if_car_driving(car_speed);
    diagnostic_datas.if_idling = check_if_car_idling(4);
    diagnostic_datas.geographic_latitude = get_geographic_latitude();
    diagnostic_datas.geographic_longitude = get_geographic_longitude();

}  






void TelemetryDevice::send_command(String command)
{
    // pid_frame frame;

    command += "\r";
    send_bluetooth_command(command);
}
String TelemetryDevice::receive_datas()
{
    String received_datas = receive_bluetooth_datas();


    return received_datas;
}

String TelemetryDevice::receive_datas_test()
{
    String received_datas = receive_bluetooth_datas_test();


    return received_datas;
}



int TelemetryDevice::decode_PID_car_speed(String frame)
{   
    Serial.println("Speed frame: " + frame);
    if(frame.length() < 8)
        return -999;
    int car_speed;
    String A_byte = String(frame.charAt(6)) + String(frame.charAt(7));
    int dec_data = std::stoi(A_byte.c_str(), 0 ,16);
    car_speed = dec_data;
    return car_speed;
}
float TelemetryDevice::decode_PID_car_rpm(String frame)
{
    if(frame.length() < 11)
        return -999;
    String A_byte = String(frame.charAt(6)) + String(frame.charAt(7));
    String B_byte = String(frame.charAt(9)) + String(frame.charAt(10));

    int dec_A = std::stoi(A_byte.c_str(), 0 ,16);
    int dec_B = std::stoi(B_byte.c_str(), 0 ,16);

    float result = (256*dec_A + dec_B)/4;

    return result;
}

bool TelemetryDevice::check_if_car_running(int car_rpm)
{
    if(car_rpm != 0)
        return true;
    return false;
}

bool TelemetryDevice::check_if_car_driving(int car_speed)
{
    if(car_speed != 0)
        return true;
    return false;
}

bool TelemetryDevice::check_if_car_idling(int car_rpm)
{
    if(car_rpm >= 600 && car_rpm <= 900)
        return true;
    return false;
}

float TelemetryDevice::decode_PID_car_fuel_level(String frame)
{
    //012F
    if(frame.length() < 8)
        return -999;
    String A_byte = String(frame.charAt(6)) + String(frame.charAt(7));

    int dec_A = std::stoi(A_byte.c_str(), 0 ,16);

    float result = (100 * dec_A)/255;
    return result;
}

/*
*/
