#ifndef HANDLER_H
#define HANDLER_H

class Handler
{
public:
    Handler(bool system_on);
    void setSystemOn();
    bool getSystemOn();

private:
    bool system_on;
};

#endif // HANDLER_H
