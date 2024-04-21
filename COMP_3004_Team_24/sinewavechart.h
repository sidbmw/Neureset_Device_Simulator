#ifndef SINEWAVECHART_H
#define SINEWAVECHART_H

#include <QChartView>
#include <QLineSeries>
#include <QtCharts>

#include "waveform_generator.h"

using namespace QtCharts;

class SineWaveChart {
   public:
    SineWaveChart(WaveformGenerator *generator);
    QChartView *displayChart(int electrodeIndex);

   private:
    WaveformGenerator *waveformGenerator;
};

#endif
