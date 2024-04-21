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
#include <QDateTime>
#include <QInputDialog>
#include <QDateTimeEdit>
#include "visual_feedback.h"
#include "sinewavechart.h"
#include "treatment_session.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <cmath>

int MainWindow::elapsedTime=141;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , batteryTimer(new QTimer(this))
    , treatmentSession(new TreatmentSession(this, generator))
    , menu(new QMenu(this))
    , newSessionAction(new QAction("New Session", this))
    , sessionLogAction(new QAction("Session Log", this))
    , dateTimeSettingAction(new QAction("Date and Time Setting", this))

{
    dateTimeEdit=NULL;
    contactLostTimer=0;
    ui->setupUi(this);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    control=new Handler(false,currentDateTime.date(),currentDateTime.time());
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

    connect(treatmentSession, &TreatmentSession::updateDisplay, this, &MainWindow::updateDisplay);

    ui->dateAndTimeDisplay->hide();
    ui->lowBatteryMsg->hide();
    // Ensure sineWaveChart is hidden initially to prevent crash
    // chartView->setVisible(false);

    //initialize battery display
    batteryProgressBar = ui -> batteryDisplay;
    batteryProgressBar->setRange(0, 100);
    batteryProgressBar->setValue(100);
    lowBatteryMsg = ui -> lowBatteryMsg;

    log = new session_log();
    endLog = new session_log();
    generator = new WaveformGenerator();

    chartUpdateTimer = new QTimer(this);
    connect(chartUpdateTimer, &QTimer::timeout, this, &MainWindow::updateEEGChart);

    // Initialize chartView to prevent crash when setting visibility
    sineWaveChart = new SineWaveChart(generator);
    chartView = sineWaveChart->displayChart(1, nullptr);
    chartView->setVisible(false); // Ensure sineWaveChart is hidden initially
    qDebug() << "[MainWindow Constructor] ChartView initialized and hidden.";
}

MainWindow::~MainWindow()
{
    cleaningTimer(); // Utilize cleaningTimer for cleanup

    delete ui;
    delete control;
    delete log;
    delete endLog;
    delete scene;
}

void MainWindow::powerButtonPressed(){
    qDebug() << "[MainWindow::powerButtonPressed] Power button pressed.";
    if (control->getSystemOn()) {
        cleaningTimer();
        control->setAllSettingToDefault();
        control->setSystemOn(false);
        displayMessage("Shutting Down...");
        batteryTimer->stop();
        ui->dateAndTimeDisplay->hide();
        ui->dateAndTimeDisplay->clear();
    } else {
        control->setSystemOn(true);
        batteryTimer->start(50000);
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
    qDebug() << "[MainWindow::menuButtonPressed] Menu button pressed.";

    control->setSessionLogOn(false);
    sessionPos = 0;

    if(control->getSystemOn()==false){

        displayMessage("Please Turn on the Device First");
    }else if(control->getMenuOn()==true){
        qDebug() << "[MainWindow::menuButtonPressed] Menu already on, returning";
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

        widgetLayout->addWidget(label1);
        widgetLayout->addWidget(label2);
        widgetLayout->addWidget(label3);
        layout->addWidget(widget);
    }
}


void MainWindow::upSelectorPressed(){
    qDebug() << "[MainWindow::upSelectorPressed] Up selector button pressed.";
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
    else if (control->getSessionLogOn()){

        std::vector<SessionData*> list = log->getSessionHistory();
        std::vector<SessionData*> endTimeList = endLog->getSessionHistory();

        if (list.empty() && endTimeList.empty()){
            sessionlabel->setText("No sessions available.");
        }
        else{

            if (sessionPos > 0){
                sessionPos--;
                QString sessionDisplayText = QString("Session #%1 \nStart: %2 \nEnd: %3").arg(sessionPos + 1).arg(list[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss")).arg(endTimeList[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss"));
                sessionlabel->setText(sessionDisplayText);
            }
        }

    }
}

void MainWindow::downSelectorPressed(){
    qDebug() << "[MainWindow::downSelectorPressed] Down selector button pressed.";
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
    else if (control->getSessionLogOn()){


        std::vector<SessionData*> list = log->getSessionHistory();
        std::vector<SessionData*> endTimeList = endLog->getSessionHistory();

        if (list.empty() && endTimeList.empty()){
            sessionlabel->setText("No sessions available.");
        }
        else{

            if (sessionPos < static_cast<int>(list.size()) - 1){
                sessionPos++;
                QString sessionDisplayText = QString("Session #%1 \nStart: %2 \nEnd: %3").arg(sessionPos + 1).arg(list[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss")).arg(endTimeList[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss"));
                sessionlabel->setText(sessionDisplayText);
            }
        }

    }
}


void MainWindow::okButtonPressed(){
    qDebug() << "[MainWindow::okButtonPressed] OK button pressed.";
    if(control->getMenuOn()){

        int current = control->getMenuPos();
        if(current==1){
            control->setMenuOn(false);
            ui->dateAndTimeDisplay->hide();
            newSession();

        }else if( current==2){
            control->setMenuOn(false);
            ui->dateAndTimeDisplay->hide();
            sessionLog();

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
    qDebug() << "[MainWindow::newSession] New session button pressed.";

    sessionEndTime = QDateTime(); // reset session end time
    elapsedTime = 141; // Reset the session duration

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

    if (!sineWaveChart) {
        sineWaveChart = new SineWaveChart(generator);
    }

    chartView = sineWaveChart->displayChart(1, nullptr);
    chartView->setVisible(false);
    widgetLayout->addWidget(chartView);


    // for session log
    QDateTime startTime;
    if (currentDateAndTime.isValid()){
        startTime = currentDateAndTime;
    }
    else{
        startTime = QDateTime::currentDateTime();
    }


    progressBarTimer = new QTimer(this);
    labelTimer=new QTimer(this);
    chartUpdateTimer=new QTimer(this);

    connect(progressBarTimer, &QTimer::timeout, [=]() {
        // Update progress bar value
        int newValue = progressBar->value() + 1;
        progressBar->setValue(newValue);

        if (newValue == 1){
            // show the graph once timer starts
            if (chartView != nullptr) {
                chartView->setVisible(true);
            }
            updateEEGChart();
        }

        // Check if progress bar is full
        if (newValue >= 100) {
            // Stop the timer when progress bar is full
            progressBarTimer->stop();
            labelTimer->stop();
            chartUpdateTimer->stop();
            currentDateAndTime = QDateTime::currentDateTime(); // reset manually set date and time
            sessionEndTime = QDateTime::currentDateTime(); // reset end time
        }
    });


    chartUpdateTimer->start(10000);

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

            sessionEndTime = QDateTime::currentDateTime();
            // if the session is completed, add it
            log->addSession(startTime);
            sessionEndTime = startTime.addSecs(141);
            endLog->addSession(sessionEndTime);
            currentDateAndTime = QDateTime::currentDateTime();
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
            chartUpdateTimer->stop();
            ui->contactIndicator->setStyleSheet("background-Color:none");
            labelTimer->stop();

            //for testing purpose i am using 30 seconds just add one more 0 then it will be good for 5 minutes
            if(contactLostTimer==30){
                powerButtonPressed();
            }
        }
    });

    connect(chartUpdateTimer, &QTimer::timeout, [=](){
         this->updateEEGChart();
    });

    contactCheckTimer->start(1000);
    if(control->getIsConnected()) {
        ui->contactIndicator->setStyleSheet("background-Color:blue");
    }


 }

void MainWindow::updateEEGChart() {
    qDebug() << "[MainWindow::updateEEGChart] Updating EEG chart.";
    if (!chartView || !chartView->chart()) {
        qDebug() << "[MainWindow::updateEEGChart] chartView or chart is null, skipping update.";
        return;
    }

    if (currentElectrode < 0 || currentElectrode >= 7) {
        currentElectrode = 0;  // Reset if out of bounds
    }

    std::vector<double> waveform = generator->generateWaveform(currentElectrode, 1);
    QLineSeries *series = new QLineSeries();
    double interval = 0.01;  // Sampling interval
    for (int i = 0; i < static_cast<int>(waveform.size()); ++i) {
        series->append(i * interval, waveform[i]);
    }

    if (chartView->chart() == nullptr) {
        chartView->setChart(new QChart());
    } else {
        chartView->chart()->removeAllSeries(); // Clear previous series
    }

    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();
    chartView->setVisible(true);

    QList<QAbstractAxis*> axes = chartView->chart()->axes();
    foreach (QAbstractAxis* axis, axes) {
        axis->setLabelsBrush(QBrush(Qt::white));
    }

    currentElectrode = (currentElectrode + 1) % 7;
}



void MainWindow::playButtonPressed() {
    qDebug() << "[MainWindow::playButtonPressed] Play button pressed.";
    // Start or resume the timer
    control->setPauseButton(false);
    if(progressBarTimer != nullptr) { // Added null check for progressBarTimer
        progressBarTimer->start(control->getTotalTimeOfTimer()/100); // Start the timer with an interval of 1 second
    }
    if(labelTimer != nullptr) { // Added null check for labelTimer
        labelTimer->start(1000);
    }
    ui->contactIndicator->setStyleSheet("background-Color:blue");
    if(chartUpdateTimer != nullptr) { // Added null check for chartUpdateTimer
        chartUpdateTimer->start();
    }
}

void MainWindow::pauseButtonPressed() {
    qDebug() << "[MainWindow::pauseButtonPressed] Pause button pressed.";
    // Pause the timer
    control->setPauseButton(true);
    if(progressBarTimer != nullptr) { // Added null check for progressBarTimer
        progressBarTimer->stop();
    }
    ui->contactIndicator->setStyleSheet("background-Color:none");
    if(labelTimer != nullptr) { // Added null check for labelTimer
        labelTimer->stop();
    }
    if(chartUpdateTimer != nullptr) { // Added null check for chartUpdateTimer
        chartUpdateTimer->stop();
    }
}

void MainWindow::resetButtonPressed() {
    qDebug() << "[MainWindow::resetButtonPressed] Reset button pressed.";
    QLabel *label=ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QLabel *>("timerLabel");
    label->setText("02:21");
    QProgressBar *progressBar =ui->mainDisplay->findChild<QWidget * >("widget")->findChild<QProgressBar *>("progressBar");
    progressBar->setValue(0);
    elapsedTime=141;
    pauseButtonPressed();

}


void MainWindow::makeContact(){
    qDebug() << "[MainWindow::makeContact] Contact on button pressed.";
    control->setIsConnected(true);
    ui->sineWaveChart->setVisible(true); // Show the sineWaveChart when contact is made
}

void MainWindow::removeContact(){
    qDebug() << "[MainWindow::removeContact] Contact off button pressed.";
    control->setIsConnected(false);
    ui->sineWaveChart->setVisible(false);
}

void MainWindow::sessionLog() {
    qDebug() << "[MainWindow::sessionLog] Entering sessionLog";


    QFrame *parentFrame = ui->mainDisplay;
    clearFrame(parentFrame);

    // select session log
    control->setSessionLogOn(true);

    // Create a layout for the parent frame
    QVBoxLayout *layout = new QVBoxLayout(parentFrame);

    // Create a new widget
    QWidget *widget = new QWidget;
    widget->setObjectName("widget");
    widget->setStyleSheet("background-color: black;");
    QVBoxLayout *widgetLayout = new QVBoxLayout(widget);
    widget->setLayout(widgetLayout);

    std::vector<SessionData*> list = log->getSessionHistory();
    std::vector<SessionData*> endTimeList = endLog->getSessionHistory();

    sessionPos= 0;

    if (list.empty() && endTimeList.empty()){
        sessionlabel = new QLabel("Empty");
    }
    else {
            QString sessionDisplayText = QString("Session #%1 \nStart: %2 \nEnd: %3").arg(sessionPos + 1).arg(list[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss")).arg(endTimeList[sessionPos]->getSessionTime().toString("yyyy-MM-dd hh:mm:ss"));
            sessionlabel = new QLabel(sessionDisplayText);
        }

    sessionlabel->setObjectName("sessionLogLabel");
    sessionlabel->setStyleSheet("color: white; font-size: 16px;font-weight: bold;");
    sessionlabel->setAlignment(Qt::AlignCenter);
    widgetLayout->addWidget(sessionlabel);

    layout->addWidget(widget);

    qDebug() << "[MainWindow::sessionLog] Session log displayed with session count: " << list.size();
}


void MainWindow::updateDisplay() {
    QString logFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + "frequency_log.txt";
    QFile logFile(logFilePath);

    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open log file for reading:" << logFile.errorString();
        return; // Make sure to return if you cannot open the file
    }

    QTextStream in(&logFile);
    QString logContent = in.readAll();
    ui->computerDisplay->setPlainText(logContent);
    logFile.close(); // Close the file after reading
}

void MainWindow::dateTimeSetting() {
    qDebug() << "[MainWindow::dateTimeSetting] Date and Time Setting button pressed.";
    cleaningTimer();
    control->setAllSettingToDefault();

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

    dateTimeEdit = new QDateTimeEdit(widget);
    dateTimeEdit->setStyleSheet("background-color: black; color: gold;");
    dateTimeEdit->setCalendarPopup(true); // Optional: enables a calendar popup for date selection
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    // Set the display format for the date and time
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd hh:mm:ss");

    widgetLayout->addWidget(dateTimeEdit);

    QPushButton *updateButton = new QPushButton("Update Date And Time", this);
    updateButton->setStyleSheet("border:1px solid white; color:gold");
    updateButton->setFixedWidth(200);
    widgetLayout->addWidget(updateButton,Qt::AlignCenter);

    // Add the DateTimeEdit widget to the layout
    layout->addWidget(widget);
    connect(updateButton, SIGNAL(clicked()), this, SLOT(displayNewDateTime()));
}

void MainWindow::displayNewDateTime() {
    qDebug() << "[MainWindow::displayNewDateTime] Update Date And Time button pressed.";
    currentDateAndTime = dateTimeEdit->dateTime();
    displayMessage("New date and time:" + currentDateAndTime.toString("yyyy-MM-dd hh:mm:ss"));

    // stop and delete previous timer if running
    if (sessionTimer) {
        sessionTimer->stop();
        delete sessionTimer;
        sessionTimer = nullptr;
    }

    sessionTimer = new QTimer(this);
    connect(sessionTimer, &QTimer::timeout, this, &MainWindow::updateTimer);
    sessionTimer->start(1000);

    QTimer::singleShot(2000, this,[this](){
        control->setMenuOn(false);
        menuButtonPressed();
    });
}

void MainWindow::updateTimer(){
    currentDateAndTime = currentDateAndTime.addSecs(1);
    ui->dateAndTimeDisplay->setText(currentDateAndTime.toString("yyyy-MM-dd hh:mm:ss"));
    ui->dateAndTimeDisplay->setStyleSheet("color: white; font-size: 6pt;");
    ui->dateAndTimeDisplay->raise();
    ui->dateAndTimeDisplay->update();
}


void MainWindow::updateBatteryDisplay() {
    int currentValue = batteryProgressBar->value();

    if (control->isConnectedToPowerSource()) {
        // If connected to power source, increase battery level
        if (currentValue < 100) {
            currentValue += 10;
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
            currentValue -= 10;
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
    qDebug() << "[MainWindow::togglePowerSource] Power source button pressed.";
    if (control->isConnectedToPowerSource()) {
        control->setConnectedToPowerSource(false);
        batteryTimer->start(50000);
        ui->powerSourceButton->setStyleSheet("background-color: red;");
    } else {
        control->setConnectedToPowerSource(true);
        batteryTimer->start(50000);
        ui->powerSourceButton->setStyleSheet("background-color: green;");
    }
}

void MainWindow::clearLowBatteryMessage() {
    lowBatteryMsg->clear();
}

void MainWindow::cleaningTimer(){

    if(chartUpdateTimer !=nullptr){
        chartUpdateTimer->stop();
        delete chartUpdateTimer;
        chartUpdateTimer=nullptr;
    }

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

    cleaningTimer();
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

void MainWindow::clearEEGChart() {

    if (chartView) {
        // Safely delete the chart if it exists
        if (chartView->chart()) {
             qDebug() << "Chart cleared";
             delete chartView;
             chartView = nullptr; // Ensure pointer is set to nullptr after deletion
        }
    }
}

void MainWindow::on_contactOnButton_clicked() {
    makeContact(); // Call makeContact when contactOnButton is clicked
}
