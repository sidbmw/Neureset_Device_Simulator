#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include "eeg_interface.h"

class TreatmentSession {
public:
    TreatmentSession(EEGInterface& eegInterface);
    ~TreatmentSession();

    // Start the treatment session
    void startSession();

private:
    EEGInterface& eegInterface;
    void calculateInitialBaseline();
    void applyTreatmentToSite(int siteIndex);
    void calculateFinalBaseline();
};

#endif 
