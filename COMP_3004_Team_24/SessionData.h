#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QDateTime>
#include <QString>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SessionData {
   public:
    SessionData(const QDateTime &startTime);
    QDateTime getSessionTime() const;
    QDateTime getSessionEndTime() const;
    void print();

   private:
    QDateTime sessionStartTime;
    QDateTime sessionEndTime;
    // need to retrieve the data for these for the PC
    vector<double> beforeDominantAverageFreqency;
    vector<double> afterDominantAverageFreqency;
};

#endif