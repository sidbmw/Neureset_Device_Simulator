#include "device_settings.h"

#include <chrono>
#include <iostream>
#include <thread>

// Constructor
DeviceSettings::DeviceSettings() {}

// Set the date
void DeviceSettings::setDate(int year, int month, int day) {
    this->year = year;
    this->month = month;
    this->day = day;
}

// Set the time
void DeviceSettings::setTime(int hour, int minute, int second) {
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

// Simulate connection loss and re-establishment
void DeviceSettings::simulateConnectionLossAndReestablishment() {
    // Simulate connection loss
    std::cout << "Connection lost. Pausing therapy session...\n";

    // Simulate waiting period for connection re-establishment
    std::this_thread::sleep_for(
        std::chrono::seconds(5));  // Simulate 5 seconds of connection loss

    // Simulate connection re-establishment
    std::cout << "Connection re-established. Resuming therapy session...\n";
}