#include "device_settings.h"

class DeviceSettings {
public:
    // Sets the date of the device
    void setDate(const Date& date);

    // Sets the time of the device
    void setTime(const Time& time);

private:
    Date deviceDate;
    Time deviceTime;
};
