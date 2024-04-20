#include "handler.h"

Handler::Handler(bool system_on, QDate date, QTime time) {
    this->system_on=system_on;
    this->menuPos=1;
    this->menuOn=false;
    this->inNewSession=false;
    this->totalTimeOfTimer=(2 * 60 + 21) * 1000;
    this->isConnected=false;
    this->pauseButton=true;
    this->sessionLogOn=false;
}

bool Handler :: getSessionLogOn(){
    return sessionLogOn;
}
void Handler::setSessionLogOn(bool b){
    this->sessionLogOn=b;
}
void Handler::setPauseButton(bool b){
    this->pauseButton=b;
}
bool Handler::getPauseButton(){
    return pauseButton;
}

void Handler::setIsConnected(bool b){
    this->isConnected=b;
}
bool Handler::getIsConnected(){
    return this->isConnected;
}


int Handler::getTotalTimeOfTimer(){
    return totalTimeOfTimer;
}

void Handler::setInNewSession(bool n){
    inNewSession=n;

}
bool Handler::getInNewSession(){
    return inNewSession;
}

void Handler::setMenuOn(bool b){
    this->menuOn=b;
}

bool Handler::getMenuOn(){
    return this->menuOn;
}

int Handler::newMenuPos(const QString &str){
    if(str=="up"){
        return menuPosUp();
    }else{
        return menuPosDown();
    }
}


int Handler::menuPosDown(){
    if(this->menuPos==3){
        this->menuPos=1;
    }else{
        this->menuPos ++;
    }
    return this->menuPos;
}
int Handler::menuPosUp(){
    if(this->menuPos==1){
        this->menuPos=3;
    }else{
        this->menuPos --;
    }
    return this->menuPos;
}

void Handler::setAllSettingToDefault(){
    setMenuPosToDefault();
    this->menuOn=false;
    setInNewSession(false);
}


void Handler::setMenuPosToDefault(){
    this->menuPos=1;
}


int Handler::getMenuPos(){
    return this->menuPos;
}

bool Handler::getSystemOn(){
    return system_on;
}

void Handler::setSystemOn(bool set){
    this->system_on=set;
}

void Handler::setConnectedToPowerSource(bool connected) {
    connectedToPowerSource = connected;
}

bool Handler::isConnectedToPowerSource() {
    return connectedToPowerSource;
}

