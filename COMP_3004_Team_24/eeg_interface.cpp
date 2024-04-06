#include "eeg_interface.h"
#include <algorithm>
#include <numeric>
#include <random>

EEGInterface::EEGInterface() {
    // Initialize mock signals for each EEG site with random values
    eegSignals.resize(21);
    std::generate(eegSignals.begin(), eegSignals.end(), []() {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0.5, 1.5); // Mock signal range
        return dis(e);
    });
}

EEGInterface::~EEGInterface() {}

void EEGInterface::initialize() {
    // initialization logic
}

double EEGInterface::readSignal(int siteIndex) {
    if (siteIndex >= 0 && siteIndex < eegSignals.size()) {
        return eegSignals[siteIndex];
    }
    return 0.0; // Return 0 if siteIndex is out of range
}

double EEGInterface::calculateBaselineFrequency(int siteIndex) {
    // Mock calculation of baseline frequency for a specific site
    return readSignal(siteIndex) + 0.1; 
}

double EEGInterface::calculateOverallBaselineFrequency() {
    // Mock calculation of overall baseline frequency
    double total = std::accumulate(eegSignals.begin(), eegSignals.end(), 0.0);
    return total / eegSignals.size();
}

void EEGInterface::applyFrequencyToSite(int siteIndex, double newFrequency) {
    // Apply the new frequency to the specified EEG site
}
