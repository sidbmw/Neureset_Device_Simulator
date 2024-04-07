#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include "eeg_interface.h"
#include "visual_feedback.h" 

class TreatmentSession {
public:
    TreatmentSession(EEGInterface& eegInterface, VisualFeedback& visualFeedback); 
    ~TreatmentSession();

    void startSession();

    void startNewSession();

    void runTreatmentCycle();

private:
    EEGInterface& eegInterface;
    VisualFeedback& visualFeedback; 
    void calculateInitialBaseline();
    void applyTreatmentToSite(int siteIndex);
    void calculateFinalBaseline();
    void manageGreenLightIndicator(bool on);
    void manageBlueLightIndicator(bool on);
    void manageRedLightIndicator(bool on);
    bool checkElectrodeContact();
    double overallBaselineFrequency; 
    double siteBaselineFrequency; 
    std::vector<double> siteBaselineFrequencies; 
    void exportSessionData() const; 
};

#endif
