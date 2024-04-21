#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QChartView>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QFrame>
#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QtCharts>

#include "eeg_interface.h"
#include "handler.h"
#include "session_log.h"
#include "sinewavechart.h"
#include "treatment_session.h"
#include "visual_feedback.h"
#include "waveform_generator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createWaveChart();
    void displaySineWaveChart();

   private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Handler *control;
    session_log *log;
    session_log *endLog;
    void clearFrame(QFrame *frame);
    QDateTime currentDateAndTime = QDateTime::currentDateTime();
    QProgressBar *batteryProgressBar;
    QLabel *lowBatteryMsg;

    QTimer *sessionTimer;
    QTimer *progressBarTimer;
    QTimer *labelTimer;
    QTimer *contactCheckTimer;
    QTimer *batteryTimer;
    int contactLostTimer;

    QMenu *menu;
    QAction *newSessionAction;
    QAction *sessionLogAction;
    QAction *dateTimeSettingAction;

    QLabel *sessionlabel;  // for session log display
    int sessionPos = 0;

    // For keeping track of session data during logs to .txt
    int sessionCount = 0;

    bool pcOn = false;

    void displayMessage(const QString &output);
    void cleaningTimer();
    static int elapsedTime;
    void cleaningIndicators();
    QDateTimeEdit *dateTimeEdit;
    QDateTime sessionEndTime;

    WaveformGenerator *generator;
    QChartView *chartView;
    QTimer *chartUpdateTimer;
    int currentElectrode;
    SineWaveChart *sineWaveChart;
    QString sessionLogFilePath;

   private slots:
    void powerButtonPressed();
    void upSelectorPressed();
    void downSelectorPressed();
    void okButtonPressed();
    void playButtonPressed();
    void pauseButtonPressed();
    void resetButtonPressed();
    void makeContact();
    void removeContact();
    void updateTimer();
    void updateBatteryDisplay();
    void clearLowBatteryMessage();
    void displayNewDateTime();
    void updateEEGChart();
    void clearEEGChart();
    void connectPC();
    void PCOutput();

   public slots:
    void menuButtonPressed();
    void newSession();
    void sessionLog();
    void dateTimeSetting();
    void togglePowerSource();
    void on_contactOnButton_clicked();
};
#endif
