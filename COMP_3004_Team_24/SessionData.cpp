#include "SessionData.h"

SessionData :: SessionData(const QDateTime& startTime){
    this->startTime = startTime;
}

QDateTime SessionData :: getSessionTime() const{
    return startTime;
}
