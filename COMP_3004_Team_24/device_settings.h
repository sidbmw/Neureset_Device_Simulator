#ifndef DEVICE_SETTINGS_H
#define DEVICE_SETTINGS_H

#include <ctime>
#include <vector>

class DeviceSettings {
   public:
    DeviceSettings();

    void setDate(int year, int month, int day);
    void setTime(int hour, int minute, int second);
    void simulateConnectionLossAndReestablishment();

   private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

#endif  // DEVICE_SETTINGS_H
