#include "sinewavechart.h"

SineWaveChart::SineWaveChart() {}

QChartView* SineWaveChart::displayChart() {
    QLineSeries *series = new QLineSeries();
    const double frequency = 1.0; // Frequency of the sine wave
    const double amplitude = 1.0; // Amplitude of the sine wave
    const double phase = 0.0; // Phase shift of the sine wave
    const int samples = 100; // Number of samples
    const double interval = 0.1; // Interval between samples
    for (int i = 0; i < samples; ++i) {
        double x = i * interval;
        double y = amplitude * qSin(2 * M_PI * frequency * x + phase);
        series->append(x, y);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Sine Wave Pattern");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(200, 150);  // Set a fixed minimum size

    return chartView;
}
