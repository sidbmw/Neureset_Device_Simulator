#include "eeg_interface.h"
#include <algorithm>
#include <numeric>
#include <random>

EEGInterface::EEGInterface() {
    // Initialize mock signals for each EEG site with random values
    signals.resize(21);
    std::generate(signals.begin(), signals.end(), []() {
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
    if (siteIndex >= 0 && siteIndex < signals.size()) {
        return signals[siteIndex];
    }
    return 0.0; // Return 0 if siteIndex is out of range
}

double EEGInterface::calculateBaselineFrequency(int siteIndex) {
    // Mock calculation of baseline frequency for a specific site
    return readSignal(siteIndex) + 0.1; 
}

double EEGInterface::calculateOverallBaselineFrequency() {
    // Mock calculation of overall baseline frequency
    double total = std::accumulate(signals.begin(), signals.end(), 0.0);
    return total / signals.size();
}
