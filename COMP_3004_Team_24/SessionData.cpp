#include "SessionData.h"

SessionData :: SessionData(const QDateTime& startTime, const QDateTime& endTime){
    this->sessionStartTime = startTime;
    this->sessionEndTime = endTime;
}

QDateTime SessionData :: getSessionStartTime() const{
    return sessionStartTime;
}

QDateTime SessionData :: getSessionEndTime() const{
    return sessionEndTime;
}

void SessionData :: print(){
    cout << "Start: " << sessionStartTime.toString("yyyy-MM-dd hh:mm:ss").toStdString() << endl;
    cout << "End: " << sessionEndTime.toString("yyyy-MM-dd hh:mm:ss").toStdString()<< endl;
}
