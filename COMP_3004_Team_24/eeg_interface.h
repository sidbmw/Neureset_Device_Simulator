#ifndef EEG_INTERFACE_H
#define EEG_INTERFACE_H

#include <vector>

class EEGInterface {
public:
    EEGInterface();
    ~EEGInterface();

    // Initializes the connection to the EEG headset
    void initialize();

    // Reads the current signal from a specific EEG site
    double readSignal(int siteIndex);

    // Calculates the baseline average frequency for a specific site
    double calculateBaselineFrequency(int siteIndex);

    // Calculates the overall baseline average frequency for all sites
    double calculateOverallBaselineFrequency();

    // Applies a new frequency to the specified EEG site
    void applyFrequencyToSite(int siteIndex, double newFrequency);

    // Generates simulated EEG data
    void generateSimulatedEEGData();

private:
    std::vector<double> eegSignals; // Mock signals for each EEG site
};

#endif 
