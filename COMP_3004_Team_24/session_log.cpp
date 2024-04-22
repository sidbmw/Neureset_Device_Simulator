#include "session_log.h"

// Constructor
session_log ::session_log() {}

// Destructor
session_log ::~session_log() {
    for (SessionData *session : sessionHistory) {
        delete session;
    }
    sessionHistory.clear();
}

// Add a session
void session_log ::addSession(const QDateTime &time) {
    SessionData *session = new SessionData(time);
    sessionHistory.push_back(session);
}

// Get session history
vector<SessionData *> session_log ::getSessionHistory() const {
    return sessionHistory;
}

// Print session log
void session_log ::print() {
    for (SessionData *s : sessionHistory) {
        s->print();
    }
}
