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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Handler *control;
    void clearFrame(QFrame *frame);
    QDateTime currentDateAndTime;
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

    void displayMessage(const QString &output);
    void cleaningTimer();
    static int elapsedTime;
    void cleaningIndicators();


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
    void updateSessionTime();
    void updateBatteryDisplay();
    void clearLowBatteryMessage();

public slots:
    void menuButtonPressed();
    void newSession();
    void sessionLog();
    void dateTimeSetting();
    void checkContactStatus();
    void contactLostTimeout();
    void togglePowerSource();

};
#endif // MAINWINDOW_H
