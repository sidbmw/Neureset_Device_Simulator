#include "eegsignalsimulator.h"
#include <random>
#include <numeric>
#include <algorithm>

EEGSignalSimulator::EEGSignalSimulator(int sites) : eegSites(sites) {}

void EEGSignalSimulator::simulateEEGData()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(10, 2); // Simulating with a mean frequency of 10Hz and std deviation of 2

    for (int i = 0; i < eegSites; ++i)
    {
        std::vector<double> siteData;
        for (int j = 0; j < 60; ++j)
        { // Simulate 60 data points per site, representing 1 minute of data
            siteData.push_back(d(gen));
        }
        eegData.push_back(siteData);
    }
}

std::vector<double> EEGSignalSimulator::calculateBaselineFrequencies()
{
    std::vector<double> baselineFrequencies;
    for (const auto &siteData : eegData)
    {
        double sum = std::accumulate(siteData.begin(), siteData.end(), 0.0);
        double mean = sum / siteData.size();
        baselineFrequencies.push_back(mean);
    }
    return baselineFrequencies;
}
