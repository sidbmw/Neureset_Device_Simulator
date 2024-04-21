#include "treatment_session.h"
#include "waveform_generator.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include <QDebug>


// treatment_session.cpp

#include "treatment_session.h"
#include "waveform_generator.h"
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QTextStream>
#include <QDebug>

TreatmentSession::~TreatmentSession() {
    // Destructor implementation
}

TreatmentSession::TreatmentSession(QObject *parent, WaveformGenerator* generator)
    : QObject(parent), waveformGenerator(generator), dominantFrequency(0) {
    // Get the directory of the project folder
    QString projectDirectory = QCoreApplication::applicationDirPath();

    // Append the log file name to the project directory
    QString logFilePath = projectDirectory + QDir::separator() + "frequency_log.txt";

    // Open the log file
    logFile.setFileName(logFilePath);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Attempting to write to:" << logFile.fileName();
        qDebug() << "Error:" << logFile.errorString();
    }
}

void TreatmentSession::logFrequency(double frequency) {
    if (!logFile.isOpen()) {
        qWarning() << "Log file is not open.";
        return;
    }
    QTextStream stream(&logFile);
    stream << "Frequency: " << frequency << "\n";
}

void TreatmentSession::processWaveform(int electrodeIndex) {
    if (!waveformGenerator) {
        qWarning() << "Waveform generator is not initialized.";
        return;
    }
    auto freqAmpPairs = waveformGenerator->getFrequencyAmplitudePairsForElectrode(electrodeIndex);
    dominantFrequency = waveformGenerator->calculateDominantFrequency(freqAmpPairs);
    logFrequency(dominantFrequency);
    emit updateDisplay(QString("Processing waveform...\n"));
}
