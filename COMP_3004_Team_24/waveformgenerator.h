#ifndef WAVEFORM_GENERATOR_H
#define WAVEFORM_GENERATOR_H

#include <vector>
#include <cmath>

class WaveformGenerator {
public:
    WaveformGenerator();
    std::vector<double> generateWaveform(int electrodeIndex, double time);

private:
    void initWaveforms();
    std::vector<std::vector<std::pair<double, double>>> waveforms; // Pair of frequency and amplitude
};

#endif // WAVEFORM_GENERATOR_H
