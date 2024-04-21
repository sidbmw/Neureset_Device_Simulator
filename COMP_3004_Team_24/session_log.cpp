#include "session_log.h"

session_log ::session_log()
{
}

session_log ::~session_log()
{
    for (SessionData *session : sessionHistory)
    {
        delete session;
    }
    sessionHistory.clear();
}

void session_log ::addSession(const QDateTime &time)
{
    SessionData *session = new SessionData(time);
    sessionHistory.push_back(session);
}

vector<SessionData *> session_log ::getSessionHistory() const
{
    return sessionHistory;
}

void session_log ::print()
{
    for (SessionData *s : sessionHistory)
    {
        s->print();
    }
}
