#ifndef HANDLER_H
#define HANDLER_H

#include <QString>
#include <QDate>

class Handler
{
public:
    Handler(bool system_on, QDate date, QTime time);
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
    void setConnectedToPowerSource(bool connected);
    bool isConnectedToPowerSource();
    bool getSessionLogOn();
    void setSessionLogOn(bool b);

private:
    int menuPosDown();
    int menuPosUp();
    bool inNewSession;
    bool system_on;
    bool menuOn;
    int menuPos; // to keep track of what option is currently selected
    int totalTimeOfTimer;
    bool isConnected;
    bool pauseButton;
    bool connectedToPowerSource;
    bool sessionLogOn; // to keep track of if the session log option is selected
};

#endif
