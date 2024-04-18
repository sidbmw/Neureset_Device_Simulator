#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QFrame>
#include "handler.h"
#include <QProgressBar>
#include <QString>
#include <QDateTime>
#include <QLabel>
#include <QDateTimeEdit>
#include <QWidget>
#include "eeg_interface.h"
#include "visual_feedback.h"
#include "treatment_session.h"
#include "session_log.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
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

    QLabel *sessionlabel; // for session log display
    int sessionPos = 0;

    void displayMessage(const QString &output);
    void cleaningTimer();
    static int elapsedTime;
    void cleaningIndicators();
    QDateTimeEdit *dateTimeEdit;
    QDateTime sessionEndTime;


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

public slots:
    void menuButtonPressed();
    void newSession();
    void sessionLog();
    void dateTimeSetting();
    // void checkContactStatus();
    // void contactLostTimeout();
    void togglePowerSource();
    void on_contactOnButton_clicked(); 
};
#endif // MAINWINDOW_H

