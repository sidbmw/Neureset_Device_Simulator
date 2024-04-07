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
<<<<<<< Updated upstream
=======
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

>>>>>>> Stashed changes

private:
    int menuPosDown();
    int menuPosUp();
    bool system_on;
    bool menuOn;
    int menuPos; //to keep track of what option is currently selected
<<<<<<< Updated upstream
=======
    int totalTimeOfTimer;
    bool isConnected;
    bool pauseButton;
    bool connectedToPowerSource;
>>>>>>> Stashed changes
};

#endif // HANDLER_H
