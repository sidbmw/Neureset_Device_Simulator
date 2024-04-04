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
    void setIsConnected(bool b);
    bool getIsConnected();
    void setPauseButton(bool b);
    bool getPauseButton();


private:
    int menuPosDown();
    int menuPosUp();
    bool inNewSession;
    bool system_on;
    bool menuOn;
    int menuPos; //to keep track of what option is currently selected
    int totalTimeOfTimer;
    bool isConnected;
    bool pauseButton;
};

#endif // HANDLER_H
