#include "session_log.h"

class SessionLog {
public:
    // Adds a new session to the log
    void addSession(const SessionData& data);

    // Retrieves session history
    std::vector<SessionData> getSessionHistory() const;

    // Exports session data to a PC
    void exportData() const;

private:
    std::vector<SessionData> sessionHistory;
};
