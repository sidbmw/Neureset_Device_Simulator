#include "device_settings.h"



DeviceSettings::DeviceSettings(){

}

void DeviceSettings::setDate(int year, int month, int day){
    this->year = year;
    this->month = month;
    this->day = day;
}

void DeviceSettings::setTime(int hour, int minute, int second){
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}
