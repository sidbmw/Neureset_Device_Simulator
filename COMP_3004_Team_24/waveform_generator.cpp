#include "waveform_generator.h"

#include <cmath>
#include <fstream>
#include <iostream>

// Constructor
WaveformGenerator::WaveformGenerator() {
    // Initialize waveforms for 7 electrodes with different frequency
    // combinations
    initWaveforms();
}

// Initialize waveforms
void WaveformGenerator::initWaveforms() {
    // Example initialization, real implementation would vary
    waveforms = {
        {{1, 0.5}, {4, 0.5}},     // Electrode 1: Delta band
        {{4, 0.5}, {8, 0.5}},     // Electrode 2: Theta band
        {{8, 0.5}, {12, 0.5}},    // Electrode 3: Alpha band
        {{12, 0.5}, {30, 0.5}},   // Electrode 4: Beta band
        {{25, 0.5}, {140, 0.5}},  // Electrode 5: Gamma band
        {{8, 0.5}, {30, 0.5}},    // Electrode 6: Alpha + Beta bands
        {{1, 0.5}, {140, 0.5}}    // Electrode 7: Delta + Gamma bands
    };
}

// Generate waveform for a given electrode and time
std::vector<double> WaveformGenerator::generateWaveform(int electrode,
                                                        double time) {
    std::vector<double> waveform;
    if (electrode < 0 || electrode >= waveforms.size()) return waveform;

    // Generate waveform based on the frequencies and amplitudes for the
    // selected electrode
    for (double t = 0; t < time;
         t += 0.01) {  // Increment by 0.01 for higher resolution
        double value = 0;
        for (auto &freqAmp : waveforms[electrode]) {
            value += freqAmp.second * sin(2 * M_PI * freqAmp.first * t);
        }
        waveform.push_back(value);
    }
    return waveform;
}

// Print waveform data to log file
void WaveformGenerator::printToLogFile(const std::string &filename,
                                       int sessionCount) {
    // Open the file in append mode
    std::ofstream logFile(filename, std::ios::app);

    // Check if the file is open and ready for writing
    if (logFile.is_open()) {
        logFile << "Session #" << sessionCount
                << " Waveform Data:\n";  // Increment and use session count
        // Loop through each electrode's waveform data
        for (int i = 0; i < waveforms.size(); ++i) {
            logFile << "Electrode " << (i + 1) << ":\n";
            for (const auto &freqAmp : waveforms[i]) {
                logFile << "Frequency: " << freqAmp.first
                        << " Hz, Amplitude: " << freqAmp.second << "\n";
            }
            double dominantFreq = calculateDominantFrequency(i);
            logFile << "Dominant Frequency: " << dominantFreq << " Hz\n";
            logFile << "----------------------------------------\n";
        }
        std::cout << "Waveform data logged to file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open log file: " << filename << std::endl;
    }

    // Close the file
    logFile.close();
}

// Calculate dominant frequency for a given electrode
double WaveformGenerator::calculateDominantFrequency(int electrode) {
    double numerator = 0.0;
    double denominator = 0.0;

    if (electrode < 0 || electrode >= waveforms.size()) return 0.0;

    // Calculate the sum of f^2 * A^2 for the numerator
    // and the sum of A^2 for the denominator
    for (auto &freqAmp : waveforms[electrode]) {
        numerator += pow(freqAmp.first, 2) * pow(freqAmp.second, 2);
        denominator += pow(freqAmp.second, 2);
    }

    // Avoid division by zero
    if (denominator == 0.0) {
        return 0.0;
    }

    // Return the dominant frequency
    return numerator / denominator;
}
