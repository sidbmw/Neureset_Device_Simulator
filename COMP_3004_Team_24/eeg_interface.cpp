#include "eeg_interface.h"
#include <algorithm>
#include <numeric>
#include <random>
#include <iostream>

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
    if (siteIndex >= 0 && siteIndex < static_cast<int>(eegSignals.size())) {
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
    // Check if the siteIndex is within the valid range
    if (siteIndex >= 0 && siteIndex < static_cast<int>(eegSignals.size())) {
        // Mock implementation: Log applying new frequency to the site
        // In a real scenario, this would interface with EEG hardware to apply the frequency
        std::cout << "Applying frequency " << newFrequency << " Hz to site " << siteIndex << std::endl;
        
        // Update the signal value for the site to simulate applying the new frequency
        // This is a simplification and in real application, the interaction with hardware would be more complex
        eegSignals[siteIndex] = newFrequency;
    } else {
        // Handle invalid siteIndex
        std::cerr << "Invalid site index: " << siteIndex << ". Cannot apply frequency." << std::endl;
    }
}
// Add a method to periodically generate simulated EEG data
void EEGInterface::generateSimulatedEEGData() {
    // Periodically update eegSignals with new simulated data
    // This is a placeholder for the actual implementation
    std::generate(eegSignals.begin(), eegSignals.end(), []() {
        static std::default_random_engine e;
        static std::uniform_real_distribution<> dis(0.5, 1.5); // Update range if needed
        return dis(e);
    });
    // This method should be called at regular intervals to simulate real-time EEG data
}
