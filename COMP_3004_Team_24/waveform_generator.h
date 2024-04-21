#ifndef WAVEFORM_GENERATOR_H
#define WAVEFORM_GENERATOR_H

#include <vector>
#include <cmath>
#include <string>

class WaveformGenerator
{
public:
    WaveformGenerator();
    std::vector<double> generateWaveform(int electrode, double time);
    void printToLogFile(const std::string &filename, int sessionCount);
    double calculateDominantFrequency(int electrode);

private:
    void initWaveforms();
    std::vector<std::vector<std::pair<double, double>>> waveforms;
};

#endif
