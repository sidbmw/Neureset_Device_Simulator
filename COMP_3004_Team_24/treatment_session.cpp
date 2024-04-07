#include "treatment_session.h"
#include "visual_feedback.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <future>

TreatmentSession::TreatmentSession(EEGInterface& eegInterface, VisualFeedback& visualFeedback) : eegInterface(eegInterface), visualFeedback(visualFeedback) {
}

TreatmentSession::~TreatmentSession() {
}

void TreatmentSession::startSession() {
    // Start the treatment session
    calculateInitialBaseline();
    runTreatmentCycle();
    calculateFinalBaseline();
    exportSessionData();
}

void TreatmentSession::runTreatmentCycle() {
    // Apply treatment to each EEG site
    for (int siteIndex = 0; siteIndex < 21; siteIndex++) {
        applyTreatmentToSite(siteIndex);
    }
}

void TreatmentSession::calculateInitialBaseline() {
    // Calculate initial baseline frequency for all EEG sites
    std::vector<std::future<double>> futures;
    for (int siteIndex = 0; siteIndex < 21; siteIndex++) {
        futures.push_back(std::async(std::launch::async, [this, siteIndex] {
            return eegInterface.calculateBaselineFrequency(siteIndex);
        }));
    }
    double totalFrequency = 0;
    for (auto& future : futures) {
        totalFrequency += future.get();
    }
    overallBaselineFrequency = totalFrequency / 21;
}

void TreatmentSession::applyTreatmentToSite(int siteIndex) {
    // Apply treatment to a specific EEG site
    siteBaselineFrequency = eegInterface.calculateBaselineFrequency(siteIndex);
    visualFeedback.turnOnGreenLight();
    for (int i = 0; i < 16; i++) {
        double offsetFrequency = 5.0;
        double newFrequency = siteBaselineFrequency + offsetFrequency;
        eegInterface.applyFrequencyToSite(siteIndex, newFrequency);
        std::this_thread::sleep_for(std::chrono::milliseconds(62));
    }
    visualFeedback.turnOffGreenLight();
    siteBaselineFrequency = eegInterface.calculateBaselineFrequency(siteIndex);
    siteBaselineFrequencies.push_back(siteBaselineFrequency);
}

void TreatmentSession::calculateFinalBaseline() {
    // Calculate final baseline frequency for all EEG sites
    std::vector<std::future<double>> futures;
    for (int siteIndex = 0; siteIndex < 21; siteIndex++) {
        futures.push_back(std::async(std::launch::async, [this, siteIndex] {
            return eegInterface.calculateBaselineFrequency(siteIndex);
        }));
    }
    double totalFrequency = 0;
    for (auto& future : futures) {
        totalFrequency += future.get();
    }
    overallBaselineFrequency = totalFrequency / 21;
}

void TreatmentSession::exportSessionData() const {
    // Export session data to a log file
    std::ofstream sessionLog("session_log.txt", std::ios::app);
    sessionLog << "Initial Overall Baseline Frequency: " << overallBaselineFrequency << "\n";
    for (int i = 0; i < siteBaselineFrequencies.size(); i++) {
        sessionLog << "Site " << i << " Baseline Frequency (Before): " << siteBaselineFrequencies[i] << "\n";
    }
    sessionLog << "Final Overall Baseline Frequency: " << overallBaselineFrequency << "\n";
    for (int i = 0; i < siteBaselineFrequencies.size(); i++) {
        sessionLog << "Site " << i << " Baseline Frequency (After): " << siteBaselineFrequencies[i] << "\n";
    }
    sessionLog << "\n";
    sessionLog.close();
}
