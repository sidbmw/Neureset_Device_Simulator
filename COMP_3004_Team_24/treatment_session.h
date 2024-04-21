#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include "eeg_interface.h"
#include "visual_feedback.h"
#include "eegsignalsimulator.h" // Include the EEGSignalSimulator header

class TreatmentSession
{
public:
    TreatmentSession(EEGInterface &eegInterface, VisualFeedback &visualFeedback);
    ~TreatmentSession();

    void startSession();
    void runTreatmentCycle();
    void applyTreatmentToSite(double baselineFrequency, int siteIndex);
    void calculateInitialBaseline();
    void calculateFinalBaseline();
    void exportSessionData() const;
    void simulateTherapySession();
    double calculateDominantFrequency();

private:
    EEGInterface &eegInterface;
    VisualFeedback &visualFeedback;
    EEGSignalSimulator eegSimulator;         // Declare eegSimulator as a member variable
    std::vector<double> baselineFrequencies; // Declare baselineFrequencies as a member variable
    double overallBaselineFrequency;
    std::vector<double> siteBaselineFrequencies;
};

#endif
