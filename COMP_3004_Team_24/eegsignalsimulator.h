#ifndef EEGSIGNALSIMULATOR_H
#define EEGSIGNALSIMULATOR_H

#include <vector>

class EEGSignalSimulator
{
public:
    EEGSignalSimulator(int sites);
    void simulateEEGData();
    std::vector<double> calculateBaselineFrequencies();

private:
    int eegSites;
    std::vector<std::vector<double>> eegData;
};

#endif
