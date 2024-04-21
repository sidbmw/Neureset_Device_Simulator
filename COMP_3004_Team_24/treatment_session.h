#ifndef TREATMENT_SESSION_H
#define TREATMENT_SESSION_H

#include <QObject>
#include <QFile>
#include "waveform_generator.h" // Include the header for WaveformGenerator

class TreatmentSession : public QObject {
    Q_OBJECT

public:
    virtual ~TreatmentSession();
    TreatmentSession(QObject *parent, WaveformGenerator* generator); // Add parameter for the generator
    void processWaveform(int electrodeIndex);
    void logFrequency(double frequency);

signals:
    void updateDisplay(const QString &text);

private:
    WaveformGenerator* waveformGenerator; // Store the reference to the generator
    double dominantFrequency;
    QFile logFile;
};

#endif // TREATMENT_SESSION_H
