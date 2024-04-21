#ifndef WAVEFORM_GENERATOR_H
#define WAVEFORM_GENERATOR_H

#include <vector>
#include <utility>

class WaveformGenerator {
public:
    WaveformGenerator();
    std::vector<double> generateWaveform(int electrode, double time);
    std::vector<std::pair<double, double>> getFrequencyAmplitudePairsForElectrode(int electrode);
    double calculateDominantFrequency(const std::vector<std::pair<double, double>>& freqAmpPairs); // Changed argument type

private:
    void initWaveforms();
    std::vector<std::vector<std::pair<double, double>>> waveforms;
};

#endif // WAVEFORM_GENERATOR_H
