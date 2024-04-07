#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <iostream>
#include <string>
#include <vector>

#include <QDateTime>

using namespace std;

class SessionData{

    public:
        SessionData(const QDateTime& startTime);
        QDateTime getSessionTime() const;

    private:
        QDateTime startTime;
        // need to retrieve the data for these for the PC
        vector<double> beforeDominantAverageFreqency;
        vector<double> afterDominantAverageFreqency;


};

#endif // SESSIONDATA_H
