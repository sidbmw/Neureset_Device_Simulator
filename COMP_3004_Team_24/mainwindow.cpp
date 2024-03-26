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
    if (control->getSystemOn()) {
        control->setSystemOn(false);
        QFrame *parentFrame = ui->mainDisplay;
        clearFrame(parentFrame);
        QVBoxLayout *layout = new QVBoxLayout(parentFrame);

        // Create a new widget
        QWidget *widget = new QWidget;

        // Set background color for the widget
        widget->setStyleSheet("background-color: black;");

        // Create a label for the message
        QLabel *label = new QLabel("Shutting Down...");
        label->setStyleSheet("color: #fff; font-size: 16px;");
        label->setAlignment(Qt::AlignCenter);

        // Create a layout for the new widget
        QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
        widget->setLayout(widgetLayout);

        // Add the label to the layout of the widget
        widgetLayout->addWidget(label);

        // Add the widget to the layout of the parent frame
        layout->addWidget(widget);

        // Start the timer to hide the widget after 2 seconds
        QTimer::singleShot(2000, widget, [widget]() {
            if (widget == nullptr) {
                qDebug() << "Widget is null";
                return;
            }
            widget->hide();
        });

    } else {

        control->setSystemOn(true);
        QFrame *parentFrame = ui->mainDisplay;
        clearFrame(parentFrame);
        QVBoxLayout *layout = new QVBoxLayout(parentFrame);

        // Create a new widget
        QWidget *widget = new QWidget;

        // Set background color for the widget
        widget->setStyleSheet("background-color: black;");

        // Create a label for the message
       QLabel *label = new QLabel("Welcome to Final Project\n\nTeam Members:\nSiddharth Natamai\nKiran Adhikari\nSydney McLeod\nKripa Adhikari\nNikhil Sharma");
        label->setStyleSheet("color: #fff; font-size: 16px;");
        label->setAlignment(Qt::AlignCenter);

        // Create a layout for the new widget
        QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
        widget->setLayout(widgetLayout);

        // Add the label to the layout of the widget
        widgetLayout->addWidget(label);

        // Add the widget to the layout of the parent frame
        layout->addWidget(widget);

        // Start the timer to hide the widget after 2 seconds
        QTimer::singleShot(3000, widget, [widget]() {
            if (widget == nullptr) {
                qDebug() << "Widget is null";
                return;
            }
            widget->hide();
        });
    }
}

void MainWindow::clearFrame(QFrame *frame) {


    QLayout *layout = frame->layout();

    if (layout) {
        // Remove the layout from the frame
        //frame->setLayout(nullptr);

        // Delete all widgets inside the layout
        while (QLayoutItem *item = layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }

        // Delete the layout itself
        delete layout;
    }
}
