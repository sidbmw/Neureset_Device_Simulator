#include "sinewavechart.h"

SineWaveChart::SineWaveChart(WaveformGenerator* generator) : waveformGenerator(generator) {}

QChartView* SineWaveChart::displayChart(int electrodeIndex, TreatmentSession *treatmentSession) {
    if (!waveformGenerator) {
        return nullptr;
    }

    QLineSeries *series = new QLineSeries();
    std::vector<double> waveform = waveformGenerator->generateWaveform(electrodeIndex, 10); // change num based on display length. I set to 10s default

    double timeIncrement = 0.01;
    for (int i = 0; i < waveform.size(); ++i) {
        series->append(i * timeIncrement, waveform[i]);
    }

    auto freqAmpPairs = waveformGenerator->getFrequencyAmplitudePairsForElectrode(electrodeIndex);
    double dominantFrequency = waveformGenerator->calculateDominantFrequency(freqAmpPairs);

    if (treatmentSession) {
        treatmentSession->logFrequency(dominantFrequency);
    }


    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("EEG Graph Display");
    chart->setTitleBrush(QBrush(Qt::white));
    chart->setBackgroundBrush(QBrush(Qt::black));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(200, 150);  // Set a fixed minimum size

    return chartView;
}

