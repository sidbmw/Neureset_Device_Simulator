#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QFrame>
#include "handler.h"
#include <QProgressBar>

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

    QTimer *sessionTimer;
    QTimer *contactLostTimer;
    QProgressBar *sessionProgressBar;

    QMenu *menu;
    QAction *newSessionAction;
    QAction *sessionLogAction;
    QAction *dateTimeSettingAction;


private slots:
    void powerButtonPressed();

public slots:
    void menuButtonPressed();
    void newSession();
    void sessionLog();
    void dateTimeSetting();
    void checkContactStatus();
    void contactLostTimeout();

};
#endif // MAINWINDOW_H
