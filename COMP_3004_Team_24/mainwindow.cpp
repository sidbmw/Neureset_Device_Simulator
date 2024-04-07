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
#include <QProgressBar>
#include <QTimer>
#include <QDateTime>
#include <QInputDialog>
#include "visual_feedback.h"

int MainWindow::elapsedTime=141;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , menu(new QMenu(this))
    , newSessionAction(new QAction("New Session", this))
    , sessionLogAction(new QAction("Session Log", this))
    , dateTimeSettingAction(new QAction("Date and Time Setting", this))
    , batteryTimer(new QTimer(this))
{
    contactLostTimer=0;
    ui->setupUi(this);
    control=new Handler(false);
    connect(ui->power, SIGNAL(clicked(bool)), this, SLOT(powerButtonPressed()));
    progressBarTimer=nullptr;
    labelTimer=nullptr;
    contactCheckTimer=nullptr;
    connect(ui->menu, SIGNAL(clicked()), this, SLOT(menuButtonPressed()));
    connect(ui->upSelector,SIGNAL(clicked(bool)), this, SLOT(upSelectorPressed()));
    connect(ui->downSelector,SIGNAL(clicked(bool)),this, SLOT(downSelectorPressed()));
    connect(ui->ok,SIGNAL(clicked(bool)),this, SLOT(okButtonPressed()));
    connect(ui->contact_on,SIGNAL(clicked(bool)),this,SLOT(makeContact()));
    connect(ui->contact_off,SIGNAL(clicked(bool)),this,SLOT(removeContact()));
    connect(batteryTimer, SIGNAL(timeout()), this, SLOT(updateBatteryDisplay()));
    connect(ui->powerSourceButton, SIGNAL(clicked()), this, SLOT(togglePowerSource()));

    ui->dateAndTimeDisplay->hide();
    ui->lowBatteryMsg->hide();

    //initialize battery display
    batteryProgressBar = ui -> batteryDisplay;
    batteryProgressBar->setRange(0, 100);
    batteryProgressBar->setValue(100);
    lowBatteryMsg = ui -> lowBatteryMsg;

    // connect(progressBarTimer, SIGNAL(timeout()), this, SLOT(checkContactStatus()));
    // connect(contactLostTimer, SIGNAL(timeout()), this, SLOT(contactLostTimeout()));
}

MainWindow::~MainWindow()
{
    if(progressBarTimer!=nullptr){
        progressBarTimer->stop();
        delete progressBarTimer;
        progressBarTimer=nullptr;
    }

    if(labelTimer!=nullptr){
        labelTimer->stop();
        delete labelTimer;
        labelTimer=nullptr;
    }

    delete ui;
    delete control;
    delete scene;
}


void MainWindow::powerButtonPressed(){
    if (control->getSystemOn()) {
        cleaningTimer();
        control->setAllSettingToDefault();
        control->setSystemOn(false);
        displayMessage("Shutting Down...");
        batteryTimer->stop();
    } else {
        control->setSystemOn(true);
        batteryTimer->start(3000);
        displayMessage("Welcome to Final Project\n\nTeam Members:\nSiddharth Natamai\nKiran Adhikari\nSydney McLeod\nKripa Adhikari\nNikhil Sharma");
        QTimer::singleShot(3000, this,[this](){
            if(!control->getMenuOn() && !control->getInNewSession()){
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
    }else if(control->getMenuOn()==true){
        return;
    }else{
        //cleaning up any session timer if it is running
        cleaningTimer();
        control->setAllSettingToDefault();
        control->setMenuOn(true);

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


//        QDateTime currentDateTime = QDateTime::currentDateTime();

//        // Extract date and time separately
//        QDate currentDate = currentDateTime.date();
//        QTime currentTime = currentDateTime.time();
//        QString dateTimeString = currentDate.toString("yyyy-MM-dd") + " " + currentTime.toString("hh:mm:ss");

//        QLabel *label4 = new QLabel(dateTimeString);
//        label4->setObjectName("dateAndTime");
//        label4->setStyleSheet("color: #fff; font-size: 8px; font-weight: bold;");
//        label4->setAlignment(Qt::AlignRight);

        // Assuming you have a QVBoxLayout for your main layout
        // Replace 'mainLayout' with your actual layout variable name
        widgetLayout->addWidget(label1);
        widgetLayout->addWidget(label2);
        widgetLayout->addWidget(label3);
//        widgetLayout->addWidget(label4,0, Qt::AlignBottom);
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
            ui->dateAndTimeDisplay->hide();
            newSession();
        }else if( current==2){
            control->setMenuOn(false);
            ui->dateAndTimeDisplay->hide();
            displayMessage("please add Code for session logs");
        }else if(current ==3 ){
            control->setMenuOn(false);
            ui->dateAndTimeDisplay->show();
            dateTimeSetting();
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
            return;
        }
        widget->hide();
    });
}

void MainWindow::newSession() { // this will be moved to session class later
    QFrame *parentFrame = ui->mainDisplay;
    clearFrame(parentFrame);
    control->setInNewSession(true);

    // Create a layout for the parent frame
    QVBoxLayout *layout = new QVBoxLayout(parentFrame);

    // Create a new widget
    QWidget *widget = new QWidget;
    widget->setObjectName("widget");
    widget->setStyleSheet("background-color: black;");
    QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
    widget->setLayout(widgetLayout);

    QLabel *label1 = new QLabel("02:21");
    label1->setObjectName("timerLabel");
    label1->setStyleSheet("color: white; font-size: 16px;font-weight: bold;");
    label1->setAlignment(Qt::AlignCenter);
    widgetLayout->addWidget(label1);

    QProgressBar *progressBar = new QProgressBar;
    progressBar->setObjectName("progressBar");
    progressBar->setRange(0, 100); // Set the range of the progress bar
    progressBar->setValue(0); // Set initial value (optional)
    progressBar->setStyleSheet("QProgressBar { border: 1px solid white; } QProgressBar::chunk { background-color: yellow;}");
    widgetLayout->addWidget(progressBar);
    layout->addWidget(widget);


    progressBarTimer = new QTimer(this);
    labelTimer=new QTimer(this);

    connect(progressBarTimer, &QTimer::timeout, [=]() {

        // Update progress bar value
        int newValue = progressBar->value() + 1;
        progressBar->setValue(newValue);
        // Check if progress bar is full
        if (newValue >= 100) {
            // Stop the timer when progress bar is full
            progressBarTimer->stop();
            labelTimer->stop();
        }
    });

    connect(labelTimer, &QTimer::timeout, [=](){

        --elapsedTime;
        int minutes = elapsedTime / 60;
        int seconds = elapsedTime % 60;
        QString labelText = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
        label1->setText(labelText);
        if (elapsedTime <= 0){
            qDebug()<<"stop";
            //add code here to check eeg value and save it in logs just check it twice so we have before and after
            labelTimer->stop();
            progressBarTimer->stop();
            contactCheckTimer->stop();


        }

        if(elapsedTime>=60 && elapsedTime <= 82){
            ui->treatmentIndicator->setStyleSheet("background-color:green");
            QTimer::singleShot(300, this, [=]() {
                ui->treatmentIndicator->setStyleSheet("background-color:none");
            });
        }

    });

    // Connect buttons to slots
    connect(ui->play, &QPushButton::clicked, this, &MainWindow::playButtonPressed);
    connect(ui->pause, &QPushButton::clicked, this, &MainWindow::pauseButtonPressed);
    connect(ui->reset, &QPushButton::clicked, this, &MainWindow::resetButtonPressed);


    contactCheckTimer=new QTimer(this);
    connect( contactCheckTimer, &QTimer::timeout, [=]() {

        if(control->getIsConnected() && (control->getPauseButton())==false){
            contactLostTimer=0;
            if(progressBarTimer->isActive()==false){
                playButtonPressed();
            }

        }

        if(control->getIsConnected()==false){
            contactLostTimer++;
            ui->contactLostIndicator->setStyleSheet("background-color:red");
            QTimer::singleShot(700, this, [=]() {
                ui->contactLostIndicator->setStyleSheet("background-color:none");
            });
            progressBarTimer->stop();
            ui->contactIndicator->setStyleSheet("background-Color:none");
            labelTimer->stop();

            //for testing purpose i am using 30 seconds just add one more 0 then it will be good for 5 minutes
            if(contactLostTimer==30){
                powerButtonPressed();
            }
        }
    });

    contactCheckTimer->start(1000);
    if(control->getIsConnected()) {
        ui->contactIndicator->setStyleSheet("background-Color:blue");
    }
 }

void MainWindow::playButtonPressed() {
    // Start or resume the timer
    control->setPauseButton(false);
    progressBarTimer->start(control->getTotalTimeOfTimer()/100); // Start the timer with an interval of 1 second
    labelTimer->start(1000);
    ui->contactIndicator->setStyleSheet("background-Color:blue");
}

void MainWindow::pauseButtonPressed() {
    // Pause the timer
    control->setPauseButton(true);
    progressBarTimer->stop();
    ui->contactIndicator->setStyleSheet("background-Color:none");
    labelTimer->stop();
}

void MainWindow::resetButtonPressed() {
    progressBarTimer->stop();
    labelTimer->stop();
    control->setPauseButton(false);
    QLabel *label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>("timerLabel");
    label->setText("02:21");
    QProgressBar *progressBar =ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QProgressBar *>("progressBar");
    progressBar->setValue(0);
    elapsedTime=141;
    pauseButtonPressed();

}


void MainWindow::makeContact(){
    control->setIsConnected(true);
}

void MainWindow::removeContact(){
    control->setIsConnected(false);
}

void MainWindow::sessionLog() { // this will be moved to session class later
    // logger for current session
    qInfo("insert loggin methods here");
}

void MainWindow::dateTimeSetting() {
    bool ok;
    QString dateAndTime = QInputDialog::getText(this, tr("Session Date & Time"), tr("Enter Date-Time"), QLineEdit::Normal, QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"), &ok);
    if (ok && !dateAndTime.isEmpty()){
        currentDateAndTime = QDateTime::fromString(dateAndTime, "yyyy-MM-dd hh:mm:ss");
//        displayMessage("Date -> " + dateAndTime);

        ui->dateAndTimeDisplay->setText((currentDateAndTime.toString("yyyy-MM-dd hh:mm:ss")));
        ui->dateAndTimeDisplay->setStyleSheet("color: white; font-size: 6pt;");

        // stop and delete previous timer if running
        if (sessionTimer) {
            sessionTimer->stop();
            delete sessionTimer;
        }

        // Start incrementing timer
        sessionTimer = new QTimer(this);
        connect(sessionTimer, &QTimer::timeout, this, &MainWindow::updateSessionTime);
        sessionTimer->start(1000);
    }
}

void MainWindow::updateSessionTime(){
    currentDateAndTime = currentDateAndTime.addSecs(1);
    ui->dateAndTimeDisplay->setText(currentDateAndTime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->dateAndTimeDisplay->raise();
    ui->dateAndTimeDisplay->update();
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

void MainWindow::updateBatteryDisplay() {
    int currentValue = batteryProgressBar->value();

    if (control->isConnectedToPowerSource()) {
        // If connected to power source, increase battery level
        if (currentValue < 100) {
            currentValue += 5;
            batteryProgressBar->setValue(currentValue);
        }
        // If battery reaches 100%, stop increasing and wait for power source button click
        if (currentValue == 100) {
            batteryTimer->stop();
            return;
        }
    } else {
        // If not connected to power source, decrease battery level
        if (currentValue > 0) {
            currentValue -= 5;
            batteryProgressBar->setValue(currentValue);
        }
        // Check if battery level drops to 0%, shutdown device
        if (currentValue == 0) {
            powerButtonPressed();
            return;
        }
    }

    // Check if battery level is below 20% to display low battery message
    if (currentValue <= 20) {
        lowBatteryMsg->setText("Low Battery! Please connect the device to a power source.");
        lowBatteryMsg->setStyleSheet("color: red;");
        lowBatteryMsg->show();
    } else {
        lowBatteryMsg->hide();
    }
}

void MainWindow::togglePowerSource() {
    if (control->isConnectedToPowerSource()) {
        control->setConnectedToPowerSource(false);
        batteryTimer->start(3000);
        ui->powerSourceButton->setStyleSheet("background-color: red;");
    } else {
        control->setConnectedToPowerSource(true);
        batteryTimer->start(3000);
        ui->powerSourceButton->setStyleSheet("background-color: green;");
    }
}

void MainWindow::clearLowBatteryMessage() {
    lowBatteryMsg->clear();
}

void MainWindow::cleaningTimer(){
    if(progressBarTimer!=nullptr){
        progressBarTimer->stop();
        delete progressBarTimer;
        progressBarTimer=nullptr;
    }

    if(labelTimer!=nullptr){
        labelTimer->stop();
        delete labelTimer;
        labelTimer=nullptr;
    }

    if(contactCheckTimer!=nullptr){
        contactCheckTimer->stop();
        delete contactCheckTimer;
        contactCheckTimer=nullptr;
    }

    cleaningIndicators();

}

void MainWindow::cleaningIndicators(){
    ui->contactIndicator->setStyleSheet("background-color:none");
    ui->contactLostIndicator->setStyleSheet("background-color:none");
    ui->treatmentIndicator->setStyleSheet("background-color:none");

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
