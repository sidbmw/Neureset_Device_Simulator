#include "SessionData.h"

SessionData ::SessionData(const QDateTime &sessionStartTime) {
    this->sessionStartTime = sessionStartTime;
}

QDateTime SessionData ::getSessionTime() const { return sessionStartTime; }

QDateTime SessionData ::getSessionEndTime() const { return sessionEndTime; }

void SessionData ::print() {
    cout << sessionStartTime.toString("yyyy-MM-dd hh:mm:ss").toStdString()
         << endl;
}
