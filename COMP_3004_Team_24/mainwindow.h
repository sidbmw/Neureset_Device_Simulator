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

    QTimer *sessionTimer;
    QTimer *progressBarTimer;
    QTimer *labelTimer;
    QTimer *contactCheckTimer;
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

public slots:
    void menuButtonPressed();
    void newSession();
    void sessionLog();
    void dateTimeSetting();
    void checkContactStatus();
    void contactLostTimeout();

};
#endif // MAINWINDOW_H
