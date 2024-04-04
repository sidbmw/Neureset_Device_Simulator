#ifndef HANDLER_H
#define HANDLER_H

#include <QString>

class Handler
{
public:
    Handler(bool system_on);
    void setSystemOn(bool set);
    bool getSystemOn();
    int newMenuPos(const QString &str);
    int getMenuPos();
    void setMenuOn(bool b);
    bool getMenuOn();
    void setMenuPosToDefault();
    void setAllSettingToDefault();
    void setInNewSession(bool n);
    bool getInNewSession();
    int getTotalTimeOfTimer();

private:
    int menuPosDown();
    int menuPosUp();
    bool inNewSession;
    bool system_on;
    bool menuOn;
    int menuPos; //to keep track of what option is currently selected
    int totalTimeOfTimer;
};

#endif // HANDLER_H
