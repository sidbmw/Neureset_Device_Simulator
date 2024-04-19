#ifndef SINEWAVECHART_H
#define SINEWAVECHART_H

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>

using namespace QtCharts;

class SineWaveChart {
public:
    SineWaveChart();
    QChartView* displayChart();
};

#endif // SINEWAVECHART_H
