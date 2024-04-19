#include "waveform_generator.h"

WaveformGenerator::WaveformGenerator() {
    // Initialize waveforms for 7 electrodes with different frequency combinations
    initWaveforms();
}

void WaveformGenerator::initWaveforms() {
    // Example initialization, real implementation would vary
    waveforms = {
        {{8, 0.5}, {12, 0.5}}, // Electrode 1: Alpha band
        {{12, 0.5}, {30, 0.5}}, // Electrode 2: Beta band
        {{1, 0.5}, {4, 0.5}}, // Electrode 3: Delta band
        {{4, 0.5}, {8, 0.5}}, // Electrode 4: Theta band
        {{25, 0.5}, {140, 0.5}}, // Electrode 5: Gamma band
        {{8, 0.5}, {30, 0.5}}, // Electrode 6: Alpha + Beta bands
        {{1, 0.5}, {140, 0.5}} // Electrode 7: Delta + Gamma bands
    };
}

std::vector<double> WaveformGenerator::generateWaveform(int electrodeIndex, double time) {
    std::vector<double> waveform;
    if (electrodeIndex < 0 || electrodeIndex >= waveforms.size()) return waveform;

    // Generate waveform based on the frequencies and amplitudes for the selected electrode
    for (double t = 0; t < time; t += 0.01) { // Increment by 0.01 for higher resolution
        double value = 0;
        for (auto& freqAmp : waveforms[electrodeIndex]) {
            value += freqAmp.second * sin(2 * M_PI * freqAmp.first * t);
        }
        waveform.push_back(value);
    }
    return waveform;
}


