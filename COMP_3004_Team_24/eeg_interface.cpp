#include "eeg_interface.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

EEGInterface::EEGInterface()
{
    // Initialize mock signals for each EEG site with random values
    eegSignals.resize(21);
    std::generate(eegSignals.begin(), eegSignals.end(), []()
                  {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0.5, 1.5); // Mock signal range
        return dis(e); });
}

EEGInterface::~EEGInterface() {}

void EEGInterface::initialize(){}

double EEGInterface::readSignal(int siteIndex)
{
    if (siteIndex >= 0 && siteIndex < static_cast<int>(eegSignals.size()))
    {
        return eegSignals[siteIndex];
    }
    return 0.0; // return 0 if out of range
}

double EEGInterface::calculateBaselineFrequency(int siteIndex)
{
    return readSignal(siteIndex) + 0.1;
}

double EEGInterface::calculateOverallBaselineFrequency()
{
    
    double total = std::accumulate(eegSignals.begin(), eegSignals.end(), 0.0);
    return total / eegSignals.size();
}

void EEGInterface::applyFrequencyToSite(int siteIndex, double newFrequency)
{
    
    if (siteIndex >= 0 && siteIndex < static_cast<int>(eegSignals.size()))
    {
        std::cout << "Applying frequency " << newFrequency << " Hz to site " << siteIndex << std::endl;
        // update signal
        eegSignals[siteIndex] = newFrequency;
    }
    else
    {
        // error handling
        std::cerr << "Invalid site index: " << siteIndex << ". Cannot apply frequency." << std::endl;
    }
}
// Add a method to periodically generate simulated EEG data
void EEGInterface::generateSimulatedEEGData()
{
    std::generate(eegSignals.begin(), eegSignals.end(), []()
                  {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0.5, 1.5);
        return dis(e); });
}
