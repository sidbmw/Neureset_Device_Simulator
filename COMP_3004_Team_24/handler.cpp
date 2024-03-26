#include "handler.h"

Handler::Handler(bool system_on) {
    this->system_on=system_on;
}

bool Handler::getSystemOn(){
    return system_on;
}

void Handler::setSystemOn(){
    this->system_on=!this->system_on;
}


