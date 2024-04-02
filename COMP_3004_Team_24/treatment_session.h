#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include "eeg_interface.h"

class TreatmentSession {
public:
    TreatmentSession(EEGInterface& eegInterface);
    ~TreatmentSession();

    void startSession();

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
