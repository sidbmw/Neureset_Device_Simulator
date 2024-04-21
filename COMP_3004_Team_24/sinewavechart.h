#ifndef SINEWAVECHART_H
#define SINEWAVECHART_H

#include "waveform_generator.h"
#include "treatment_session.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

using namespace QtCharts;

class SineWaveChart {
public:
    SineWaveChart(WaveformGenerator* generator);
    QChartView* displayChart(int electrodeIndex, TreatmentSession *treatmentSession);

private:
    WaveformGenerator* waveformGenerator;
};

#endif // SINEWAVECHART_H
