#include "SessionData.h"

SessionData :: SessionData(const QDateTime& startTime){
    this->startTime = startTime;
}

QDateTime SessionData :: getSessionTime() const{
    return startTime;
}

void SessionData :: print(){
    cout << startTime.toString("yyyy-MM-dd hh:mm:ss").toStdString() << endl;
}
