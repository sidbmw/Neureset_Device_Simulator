#include "treatment_session.h"

TreatmentSession::TreatmentSession(EEGInterface& eegInterface) : eegInterface(eegInterface) {

}

TreatmentSession::~TreatmentSession() {

}

void TreatmentSession::startSession() {

}

void TreatmentSession::startNewSession() {

}

void TreatmentSession::runTreatmentCycle() {

}

void TreatmentSession::calculateInitialBaseline() {

}

void TreatmentSession::applyTreatmentToSite(int siteIndex) {

}

void TreatmentSession::calculateFinalBaseline() {

}

void TreatmentSession::manageGreenLightIndicator(bool on) {

}

void TreatmentSession::manageBlueLightIndicator(bool on) {

}

void TreatmentSession::manageRedLightIndicator(bool on) {

}

bool TreatmentSession::checkElectrodeContact() {
    return true;
}
