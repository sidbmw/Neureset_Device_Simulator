#include "SessionData.h"

// Constructor
SessionData ::SessionData(const QDateTime &sessionStartTime) {
    this->sessionStartTime = sessionStartTime;
}

// Get session start time
QDateTime SessionData ::getSessionTime() const { return sessionStartTime; }

// Get session end time
QDateTime SessionData ::getSessionEndTime() const { return sessionEndTime; }

// Print session start time
void SessionData ::print() {
    cout << sessionStartTime.toString("yyyy-MM-dd hh:mm:ss").toStdString()
         << endl;
}
