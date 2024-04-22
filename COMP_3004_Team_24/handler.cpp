#include "handler.h"

// Constructor
Handler::Handler(bool system_on, QDate date, QTime time) {
    this->system_on = system_on;
    this->menuPos = 1;
    this->menuOn = false;
    this->inNewSession = false;
    this->totalTimeOfTimer = (2 * 60 + 21) * 1000;
    this->isConnected = false;
    this->pauseButton = false;
    this->sessionLogOn = false;
}

// Returns the session log status
bool Handler ::getSessionLogOn() { return sessionLogOn; }

// Sets the session log status
void Handler::setSessionLogOn(bool b) { this->sessionLogOn = b; }

// Sets the pause button status
void Handler::setPauseButton(bool b) { this->pauseButton = b; }

// Returns the pause button status
bool Handler::getPauseButton() { return pauseButton; }

// Sets the connection status
void Handler::setIsConnected(bool b) { this->isConnected = b; }

// Returns the connection status
bool Handler::getIsConnected() { return this->isConnected; }

// Returns the total time of the timer
int Handler::getTotalTimeOfTimer() { return totalTimeOfTimer; }

// Sets the new session status
void Handler::setInNewSession(bool n) { inNewSession = n; }

// Returns the new session status
bool Handler::getInNewSession() { return inNewSession; }

// Sets the menu status
void Handler::setMenuOn(bool b) { this->menuOn = b; }

// Returns the menu status
bool Handler::getMenuOn() { return this->menuOn; }

// Determines new menu position based on input
int Handler::newMenuPos(const QString &str) {
    if (str == "up") {
        return menuPosUp();
    } else {
        return menuPosDown();
    }
}

// Moves the menu position down
int Handler::menuPosDown() {
    if (this->menuPos == 3) {
        this->menuPos = 1;
    } else {
        this->menuPos++;
    }
    return this->menuPos;
}

// Moves the menu position up
int Handler::menuPosUp() {
    if (this->menuPos == 1) {
        this->menuPos = 3;
    } else {
        this->menuPos--;
    }
    return this->menuPos;
}

// Resets all settings to default
void Handler::setAllSettingToDefault() {
    setMenuPosToDefault();
    this->menuOn = false;
    setInNewSession(false);
}

// Resets the menu position to default
void Handler::setMenuPosToDefault() { this->menuPos = 1; }

// Returns the menu position
int Handler::getMenuPos() { return this->menuPos; }

// Returns the system status
bool Handler::getSystemOn() { return system_on; }

// Sets the system status
void Handler::setSystemOn(bool set) { this->system_on = set; }

// Sets the power source connection status
void Handler::setConnectedToPowerSource(bool connected) {
    connectedToPowerSource = connected;
}

// Returns the power source connection status
bool Handler::isConnectedToPowerSource() { return connectedToPowerSource; }
