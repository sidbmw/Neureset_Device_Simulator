#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include "eeg_interface.h"

class TreatmentSession {
public:
    TreatmentSession(EEGInterface& eegInterface);
    ~TreatmentSession();

    // Starts the treatment session
    void startSession();

    // Starts a new session with electrode contact check and visual feedback management
    void startNewSession();

    void runTreatmentCycle();

private:
    EEGInterface& eegInterface;
    void calculateInitialBaseline();
    void applyTreatmentToSite(int siteIndex);
    void calculateFinalBaseline();
    void manageGreenLightIndicator(bool on);
    void manageBlueLightIndicator(bool on);
    void manageRedLightIndicator(bool on);
    bool checkElectrodeContact();
};

#endif 
