#include "handler.h"

Handler::Handler(bool system_on) {
    this->system_on=system_on;
    this->menuPos=1;
    this->menuOn=false;
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


