#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    control=new Handler(false);
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(powerButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete control;
     delete ui;
    delete scene;

}

void MainWindow::powerButtonPressed(){
    if(control->getSystemOn()){
        QFrame *frame = ui->mainDisplay;
        clearFrame(frame);
        frame->setStyleSheet("background-color: black;"); // White background
        frame->setFrameStyle(QFrame::Box | QFrame::Raised);

        // Create message label
        QLabel *label = new QLabel("Shutting Down");
        label->setStyleSheet("color: #ffffff; font-size: 16px;"); // Black text
        label->setAlignment(Qt::AlignCenter);
        frame->setLayout(new QVBoxLayout(frame));
        frame->layout()->addWidget(label);

        // Fade in animation
        QPropertyAnimation *animation = new QPropertyAnimation(frame, "opacity");
        animation->setDuration(1000); // 1 second
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        QTimer::singleShot(1000, this, [label]() {
            label->hide();
        });
        qDebug()<<"System is On";

    }else{
        control->setSystemOn();
        QFrame *frame = ui->mainDisplay;
        frame->setStyleSheet("background-color: black;"); // White background
        frame->setFrameStyle(QFrame::Box | QFrame::Raised);

        // Create message label
        QLabel *label = new QLabel("Welcome to Final Project\n\nTeam Members:\nSiddharth Natamai\nKiran Adhikari\nSydney McLeod\nKripa Adhikari\nNikhil Sharma");
        label->setStyleSheet("color: #ffffff; font-size: 16px;"); // Black text
        label->setAlignment(Qt::AlignCenter);
        frame->setLayout(new QVBoxLayout(frame));
        frame->layout()->addWidget(label);

        // Fade in animation
        QPropertyAnimation *animation = new QPropertyAnimation(frame, "opacity");
        animation->setDuration(1000); // 1 second
        animation->setStartValue(0);
        animation->setEndValue(1);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        QTimer::singleShot(5000, this, [label]() {
            label->hide();
        });

    }

}


void MainWindow::clearFrame(QFrame *frame) {
    QLayout *layout = frame->layout();
    if (layout) {
        while (QLayoutItem *item = layout->takeAt(0)) {
            delete item->widget(); // Delete widget
            delete item; // Delete layout item
        }
        delete layout; // Delete layout
    }
}



