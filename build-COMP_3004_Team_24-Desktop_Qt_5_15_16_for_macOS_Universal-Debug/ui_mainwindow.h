/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QFrame *mainDisplay;
    QPushButton *menu;
    QFrame *contactIndicator;
    QFrame *treatmentIndicator;
    QFrame *contactLostIndicator;
    QPushButton *power;
    QPushButton *upSelector;
    QPushButton *downSelector;
    QPushButton *play;
    QPushButton *pause;
    QPushButton *stop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(799, 486);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(30, 10, 741, 401));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        mainDisplay = new QFrame(frame);
        mainDisplay->setObjectName(QString::fromUtf8("mainDisplay"));
        mainDisplay->setGeometry(QRect(110, 90, 481, 221));
        mainDisplay->setFrameShape(QFrame::StyledPanel);
        mainDisplay->setFrameShadow(QFrame::Raised);
        menu = new QPushButton(frame);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu->setGeometry(QRect(110, 50, 31, 32));
        menu->setStyleSheet(QString::fromUtf8("/* Apply to QPushButton */\n"
"\n"
"    background-color: transparent;\n"
"    border: none;\n"
"    background: none;\n"
"    background-repeat: no-repeat;\n"
"    border-image: url(\":/images/bars-solid.svg\");\n"
"    \n"
""));
        contactIndicator = new QFrame(frame);
        contactIndicator->setObjectName(QString::fromUtf8("contactIndicator"));
        contactIndicator->setGeometry(QRect(10, 10, 21, 21));
        contactIndicator->setFrameShape(QFrame::StyledPanel);
        contactIndicator->setFrameShadow(QFrame::Raised);
        treatmentIndicator = new QFrame(frame);
        treatmentIndicator->setObjectName(QString::fromUtf8("treatmentIndicator"));
        treatmentIndicator->setGeometry(QRect(40, 10, 21, 21));
        treatmentIndicator->setFrameShape(QFrame::StyledPanel);
        treatmentIndicator->setFrameShadow(QFrame::Raised);
        contactLostIndicator = new QFrame(frame);
        contactLostIndicator->setObjectName(QString::fromUtf8("contactLostIndicator"));
        contactLostIndicator->setGeometry(QRect(70, 10, 21, 21));
        contactLostIndicator->setFrameShape(QFrame::StyledPanel);
        contactLostIndicator->setFrameShadow(QFrame::Raised);
        power = new QPushButton(frame);
        power->setObjectName(QString::fromUtf8("power"));
        power->setGeometry(QRect(680, 20, 31, 32));
        power->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/power-off-solid.svg\");\n"
"\n"
""));
        upSelector = new QPushButton(frame);
        upSelector->setObjectName(QString::fromUtf8("upSelector"));
        upSelector->setGeometry(QRect(610, 140, 31, 32));
        upSelector->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/circle-up-solid.svg\");\n"
"\n"
""));
        downSelector = new QPushButton(frame);
        downSelector->setObjectName(QString::fromUtf8("downSelector"));
        downSelector->setGeometry(QRect(610, 210, 31, 32));
        downSelector->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/circle-down-solid.svg\");\n"
"\n"
""));
        play = new QPushButton(frame);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(280, 330, 21, 32));
        play->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/play-solid.svg\");\n"
"\n"
""));
        pause = new QPushButton(frame);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setGeometry(QRect(330, 330, 21, 32));
        pause->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/pause-solid.svg\");\n"
"\n"
""));
        stop = new QPushButton(frame);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(380, 330, 21, 32));
        stop->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"border: none;\n"
"background: none;\n"
"background-repeat: no-repeat;\n"
"border-image: url(\":/images/stop-solid.svg\");\n"
"\n"
""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 799, 37));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        menu->setText(QString());
        power->setText(QString());
        upSelector->setText(QString());
        downSelector->setText(QString());
        play->setText(QString());
        pause->setText(QString());
        stop->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
