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

    QDateTime currentDateAndTime; // this should later be converted to a property of session class once we have a session class so we can have date&time for every session.
    QTimer *sessionTimer;
    QTimer *contactLostTimer;
    QProgressBar *sessionProgressBar;

    QMenu *menu;
    QAction *newSessionAction;
    QAction *sessionLogAction;
    QAction *dateTimeSettingAction;
    void displayMessage(const QString &output);


private slots:
    void powerButtonPressed();
    void upSelectorPressed();
    void downSelectorPressed();
    void okButtonPressed();
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
