#ifndef SINEWAVECHART_H
#define SINEWAVECHART_H

#include "waveform_generator.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

using namespace QtCharts;

class SineWaveChart
{
public:
    SineWaveChart(WaveformGenerator *generator);
    QChartView *displayChart(int electrodeIndex);

private:
    WaveformGenerator *waveformGenerator;
};

#endif
