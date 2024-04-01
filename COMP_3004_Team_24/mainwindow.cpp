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

    , menu(new QMenu(this))
    , newSessionAction(new QAction("New Session", this))
    , sessionLogAction(new QAction("Session Log", this))
    , dateTimeSettingAction(new QAction("Date and Time Setting", this))
{
    ui->setupUi(this);
    control=new Handler(false);
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(powerButtonPressed()));

    connect(ui->menu, SIGNAL(clicked()), this, SLOT(menuButtonPressed()));
    connect(ui->upSelector,SIGNAL(clicked(bool)), this, SLOT(upSelectorPressed()));
    connect(ui->downSelector,SIGNAL(clicked(bool)),this, SLOT(downSelectorPressed()));
    connect(ui->ok,SIGNAL(clicked(bool)),this, SLOT(okButtonPressed()));
    // connect(sessionTimer, SIGNAL(timeout()), this, SLOT(checkContactStatus()));
    // connect(contactLostTimer, SIGNAL(timeout()), this, SLOT(contactLostTimeout()));
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
        displayMessage("Shutting Down...");
    } else {

        control->setSystemOn(true);
        displayMessage("Welcome to Final Project\n\nTeam Members:\nSiddharth Natamai\nKiran Adhikari\nSydney McLeod\nKripa Adhikari\nNikhil Sharma");
        QTimer::singleShot(3000, this,[this](){
            if(this->control->getSystemOn()){
                menuButtonPressed();
            }else{
                return;
            }
        });
    }
}

void MainWindow::menuButtonPressed() {

    if(control->getSystemOn()==false){
        displayMessage("Please Turn on the Device First");
    }else{
        control->setMenuOn(true);
        control->setMenuPosToDefault();
        QFrame *parentFrame = ui->mainDisplay;
        clearFrame(parentFrame);

        // Create a layout for the parent frame
        QVBoxLayout *layout = new QVBoxLayout(parentFrame);

        // Create a new widget
        QWidget *widget = new QWidget;
        widget->setObjectName("widget");
        widget->setStyleSheet("background-color: black;");

        // Create a layout for the widget
        QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
        widget->setLayout(widgetLayout);

        QLabel *label1 = new QLabel("New Session");
        label1->setObjectName("label1");
        label1->setStyleSheet("color: yellow; font-size: 16px;font-weight: bold;");
        label1->setAlignment(Qt::AlignCenter);

        QLabel *label2 = new QLabel("Session Log");
        label2->setObjectName("label2");
        label2->setStyleSheet("color: #fff; font-size: 16px;");
        label2->setAlignment(Qt::AlignCenter);

        QLabel *label3 = new QLabel("Date and Time Setting");
        label3->setObjectName("label3");
        label3->setStyleSheet("color: #fff; font-size: 16px;");
        label3->setAlignment(Qt::AlignCenter);

        widgetLayout->addWidget(label1);
        widgetLayout->addWidget(label2);
        widgetLayout->addWidget(label3);
        layout->addWidget(widget);


    }
}


void MainWindow::upSelectorPressed(){
    if(control->getMenuOn()){
        int current = control->getMenuPos();
        QString temp = "label" + QString::number(current);
        QLabel *label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>(temp);
        if(label){
            label->setStyleSheet("color:white;font-size: 16px;");
        }
        current=control->newMenuPos("up");
        temp="label" + QString::number(current);
        label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>(temp);
        if(label){
            label->setStyleSheet("color:yellow;font-size: 16px;font-weight: bold;");
        }

    }
}

void MainWindow::downSelectorPressed(){
    if(control->getMenuOn()){
        int current = control->getMenuPos();
        QString temp = "label" + QString::number(current);
        QLabel *label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>(temp);
        if(label){
            label->setStyleSheet("color:white;font-size: 16px;");
        }
        current=control->newMenuPos("down");
        temp="label" + QString::number(current);
        label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>(temp);
        if(label){
            label->setStyleSheet("color:yellow;font-size: 16px;font-weight: bold;");
        }

    }
}


void MainWindow::okButtonPressed(){
    if(control->getMenuOn()){

        int current = control->getMenuPos();
        if(current==1){
            control->setMenuOn(false);
            displayMessage("please add Code for New Session");
        }else if( current==2){
            control->setMenuOn(false);
            displayMessage("please add Code for session logs");
        }else if(current ==3 ){
            control->setMenuOn(false);
            displayMessage("please add Code for set date and time");
        }
    }
}
void MainWindow::displayMessage(const QString &output){
    QFrame *parentFrame = ui->mainDisplay;
    clearFrame(parentFrame);
    QVBoxLayout *layout = new QVBoxLayout(parentFrame);

    // Create a new widget
    QWidget *widget = new QWidget;

    // Set background color for the widget
    widget->setStyleSheet("background-color: black;");

    // Create a label for the message
    QLabel *label = new QLabel(output);
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

void MainWindow::newSession() { // this will be moved to session class later
    // Creates a new session
    qInfo("new session pressed.");
}

void MainWindow::sessionLog() { // this will be moved to session class later
    // logger for current session
    qInfo("insert loggin methods here");
}

void MainWindow::dateTimeSetting() { // this will be moved to date&time class later
    // dislay date & time settings
    qInfo("display date and time");
}

void MainWindow::checkContactStatus(){
    // check for contact for 5 minutes
    // if no contact after 5 min, turn off device
    // erase current session
}

void MainWindow::contactLostTimeout(){
    // red light flases
    // session is paused
    // device starts beeping until contact is reestablished
}

void MainWindow::clearFrame(QFrame *frame) {


    QLayout *layout = frame->layout();

    if (layout) {


        // Delete all widgets inside the layout
        while (QLayoutItem *item = layout->takeAt(0)) {
            delete item->widget();
            delete item;
        }

        // Delete the layout itself
        delete layout;
    }
}
