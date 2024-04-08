#ifndef SESSION_LOG_H
#define SESSION_LOG_H

#include <iostream>
#include <vector>

#include "SessionData.h"

using namespace std;

class session_log {

public:
    session_log();
    ~session_log();

    void exportData() const;

    //void addSession(const SessionData& data);

    void addSession(const QDateTime& time);

    vector<SessionData*> getSessionHistory() const;

    void print();

private:
    vector<SessionData*> sessionHistory;
};


#endif // SESSION_LOG_H
