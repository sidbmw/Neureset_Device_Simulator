#include "treatment_session.h"
#include "visual_feedback.h"
#include "eegsignalsimulator.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <vector>
#include <future>
#include <iostream>

TreatmentSession::TreatmentSession(EEGInterface &eegInterface, VisualFeedback &visualFeedback) : eegInterface(eegInterface), visualFeedback(visualFeedback), eegSimulator(21)
{
    eegSimulator.simulateEEGData();
    baselineFrequencies = eegSimulator.calculateBaselineFrequencies();
}

TreatmentSession::~TreatmentSession()
{
}

void TreatmentSession::startSession()
{
    // Start the treatment session
    calculateInitialBaseline();
    runTreatmentCycle();
    calculateFinalBaseline();
    exportSessionData();
}

void TreatmentSession::runTreatmentCycle()
{
    // Apply treatment to each EEG site
    for (int siteIndex = 0; siteIndex < 21; siteIndex++)
    {
        double baselineFrequency = baselineFrequencies[siteIndex];
        applyTreatmentToSite(baselineFrequency, siteIndex);
    }
}

void TreatmentSession::calculateInitialBaseline()
{
    // Calculate initial baseline frequency for all EEG sites
    std::vector<std::future<double>> futures;
    for (int siteIndex = 0; siteIndex < 21; siteIndex++)
    {
        futures.push_back(std::async(std::launch::async, [this, siteIndex]
                                     { return eegInterface.calculateBaselineFrequency(siteIndex); }));
    }
    double totalFrequency = 0;
    for (auto &future : futures)
    {
        totalFrequency += future.get();
    }
    overallBaselineFrequency = totalFrequency / 21;
}

void TreatmentSession::applyTreatmentToSite(double baselineFrequency, int siteIndex)
{
    const double offsetFrequency = 5.0; // Hz
    double currentFrequency = baselineFrequency;
    for (int i = 0; i < 16; ++i)
    { // Apply treatment every 1/16th of a second for 1 second
        currentFrequency += offsetFrequency;
        // Simulate recalculating the brainwave frequency and applying the offset
        std::this_thread::sleep_for(std::chrono::milliseconds(62)); // Simulate time delay
    }
    // Store or process the final frequency for the site after treatment
    siteBaselineFrequencies.push_back(currentFrequency);
}

void TreatmentSession::calculateFinalBaseline()
{
    // Calculate final baseline frequency for all EEG sites
    std::vector<std::future<double>> futures;
    for (int siteIndex = 0; siteIndex < 21; siteIndex++)
    {
        futures.push_back(std::async(std::launch::async, [this, siteIndex]
                                     { return eegInterface.calculateBaselineFrequency(siteIndex); }));
    }
    double totalFrequency = 0;
    for (auto &future : futures)
    {
        totalFrequency += future.get();
    }
    overallBaselineFrequency = totalFrequency / 21;
}

void TreatmentSession::exportSessionData() const
{
    // Export session data to a log file
    std::ofstream sessionLog("session_log.txt", std::ios::app);
    sessionLog << "Initial Overall Baseline Frequency: " << overallBaselineFrequency << "\n";
    for (int i = 0; i < static_cast<int>(siteBaselineFrequencies.size()); i++)
    {
        sessionLog << "Site " << i << " Baseline Frequency (Before): " << siteBaselineFrequencies[i] << "\n";
    }
    sessionLog << "Final Overall Baseline Frequency: " << overallBaselineFrequency << "\n";
    for (int i = 0; i < static_cast<int>(siteBaselineFrequencies.size()); i++)
    {
        sessionLog << "Site " << i << " Baseline Frequency (After): " << siteBaselineFrequencies[i] << "\n";
    }
    sessionLog << "\n";
    sessionLog.close();
}
// Implement therapy session simulation with adjusted timing for testing
void TreatmentSession::simulateTherapySession()
{
    std::cout << "Starting therapy session simulation...\n";
    for (int round = 1; round <= 4; ++round)
    {
        std::cout << "Round " << round << " of therapy\n";
        // Simulate 5 seconds for analysis
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Processing input waveform\n";
        // Simulate calculating dominant frequency
        double dominantFrequency = calculateDominantFrequency();
        std::cout << "Dominant frequency calculated: " << dominantFrequency << "\n";
        // Simulate delivering 1 sec feedback
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Delivering feedback\n";
    }
    // Simulate final analysis of 5 sec
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Therapy finished\n";
}

double TreatmentSession::calculateDominantFrequency()
{
    // Placeholder for dominant frequency calculation logic
    // Simplified dominant frequency calculation
    double f1 = 8.0, A1 = 0.5; // Example values for frequency and amplitude
    double f2 = 12.0, A2 = 0.5;
    double f3 = 30.0, A3 = 0.5;
    double fd = (f1 * A1 * A1 + f2 * A2 * A2 + f3 * A3 * A3) / (A1 * A1 + A2 * A2 + A3 * A3);
    return fd; // Return the calculated dominant frequency
}