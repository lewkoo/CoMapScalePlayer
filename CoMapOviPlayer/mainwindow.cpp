#include <QtGui>
#include <QTimer>
#include <QEventLoop>
#include <QtNetwork>
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"
#include <stdlib.h>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mappingwidget.h"

const QString MainWindow::NOT_CONNECTED_TEXT = QString("Not Connected");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mapWidget(NULL)
{
    ui->setupUi(this);

    currAction=0;
    totalActions=0;
    actionsLeft = 0;
    pause = false;

    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->btnLoad, SIGNAL(clicked()), this, SLOT(loadIcons()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clearMapObjects()));
    connect(ui->btnLoadLogFile, SIGNAL(clicked()), this, SLOT(loadDataLog()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(startPlayback()));
    connect(ui->btnPause, SIGNAL(clicked()), this, SLOT(switchPause()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addMapWidget(MappingWidget* mapWidget)
{
    this->mapWidget = mapWidget;

    //QDockWidget *dockWidget = new QDockWidget(tr("Map"), this);
    //dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    //dockWidget->setWidget(mapWidget);

    mapWidget->setParent(this);
    ui->gridLayout->addWidget(mapWidget, 0, 1);

    //addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    //dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
}

void MainWindow::startPlayback(){

    pause = false;

    totalActions = eventManager.getLength();
    ui->horizontalSlider->setMaximum(totalActions);

    int timeToWait;
    QTime currTime;
    QTime nextTime;

    Event* currEvent;
    Event* nextEvent;

    //check if the file has been loaded
    updateUi();

    if(eventManager.isInicialized()){
         qDebug()<< "Playback started";
         ui->lblStatus->setText("Playback started");

         currEvent = eventManager.getNextEvent();
         currTime = currEvent->getTime();
         nextEvent = eventManager.getNextEvent();
         nextTime = nextEvent->getTime();
         updateUi();

         timeToWait = abs(nextTime.msecsTo(currTime));
         qDebug("value = %d", timeToWait);

         //mapWidget->mapPositionChanged(currEvent->getPos());
         mapWidget->mapBoxChanged(currEvent->getBox());
         mapWidget->update();
         updateUi();
         //ui->lblNumSteps->setText(numSteps.setNum(counter));



         //sleeping for x msecs
         QTimer timer;
         timer.start(timeToWait);
         QEventLoop loop;
         connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
         loop.exec();

         //execute the next event
        //mapWidget->mapPositionChanged(nextEvent->getPos());
         mapWidget->mapBoxChanged(currEvent->getBox());
         mapWidget->update();
         updateUi();
         //ui->lblNumSteps->setText(numSteps.setNum(counter));


         //mapWidget->mapScaleChanged(nextEvent->getScale());

         currEvent = nextEvent;


         while(eventManager.getLength() >= 1 && pause == false){

             if(pause == true){
                 ui->lblStatus->setText("Playback finished");
             }

            nextEvent = eventManager.getNextEvent();
           // counter--;
            currTime = currEvent->getTime();
            nextTime = nextEvent->getTime();
            timeToWait = abs(nextTime.msecsTo(currTime));
            qDebug("value = %d", timeToWait);

           // mapWidget->mapPositionChanged(currEvent->getPos());
              mapWidget->mapBoxChanged(currEvent->getBox());
              mapWidget->update();
              updateUi();
             // ui->lblNumSteps->setText(numSteps.setNum(counter));


            //sleeping for x msecs
            QTimer timer;
            timer.start(timeToWait);
            QEventLoop loop;
            connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
            loop.exec();

            //mapWidget->mapPositionChanged(nextEvent->getPos());
            mapWidget->mapBoxChanged(nextEvent->getBox());
            mapWidget->update();
            updateUi();
            //ui->lblNumSteps->setText(numSteps.setNum(counter));

            //mapWidget->mapScaleChanged(nextEvent->getScale());

            currEvent = nextEvent;
        }

         //qDebug() << counter;
         if(pause == true){
             ui->lblStatus->setText("Playback paused");
         }else{
         qDebug() <<"Playback finished";
         ui->lblStatus->setText("Playback finished");
         }
    }else{
        qDebug()<< "No file has been loaded";
        ui->lblStatus->setText("Load a data log first");
    }




}

void MainWindow::updateUi(){
    QString numSteps;
    actionsLeft=eventManager.getLength();
    currAction = totalActions-actionsLeft;
    ui->lblNumSteps->setText(numSteps.setNum(actionsLeft));
    ui->horizontalSlider->setSliderPosition(currAction);

}

//void MainWindow::startServer()
//{

//    ui->chkWedge->setEnabled(true);
//    ui->chkObjWedge->setEnabled(ui->chkWedge->checkState());
//    ui->chkVw->setEnabled(true);

//    //Give map widget a handle to client data
//    if (mapWidget != NULL)
//    {
//       // mapWidget->setClientList(server->getClientList());
//    }


//    QString ipAddress;
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
//    // use the first non-localhost IPv4 address
//    for (int i = 0; i < ipAddressesList.size(); ++i)
//    {
//        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//            ipAddressesList.at(i).toIPv4Address())
//        {
//            ipAddress = ipAddressesList.at(i).toString();
//            break;
//        }
//    }
//    // if we did not find one, use IPv4 localhost
//    if (ipAddress.isEmpty())
//        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
//    ui->lblStatus->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
//                            "Ready for N900 connections.")
//                           .arg(ipAddress).arg(server->serverPort()));
//}

//void MainWindow::stopServer()
//{
//    delete server;
//    server = NULL;

//    ui->chkWedge->setEnabled(false);
//    ui->chkObjWedge->setEnabled(false);
//    ui->chkVw->setEnabled(false);

//    ui->lblStatus->setText(NOT_CONNECTED_TEXT);
//}

void MainWindow::loadIcons()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/bens/Code/CoMapOvi_MapData", tr("CSV files (*.csv)"));
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList lineList;
        QTextStream stream(&file);

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            lineList.append(line);
        }

        mapWidget->addIcons(lineList);
    }
    else
    {
        qDebug() << "Can't open file " + fileName;
    }
}

void MainWindow::clearMapObjects()
{
    mapWidget->clearMapObjects();
}

int MainWindow::loadDataLog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)"));
    int lastSlash = fileName.lastIndexOf('/');
    QString fileInfo = fileName;
    fileInfo.remove(0, lastSlash + 1);
    QFile file(fileName);
    Event::EventType eventType;
    int userId;
    int error = 0;
    bool parseOk = true;
    bool nameOk = true;
    const char DELIM = ';';

    if (fileInfo.startsWith("Pos"))
    {
        eventType = Event::NavEvent;
        userId =  QString(fileInfo.at(3)).toInt(&parseOk);
    }
    else if (fileInfo.startsWith("Vw"))
    {
        eventType = Event::AnchorEvent;
        userId =  QString(fileInfo.at(2)).toInt(&parseOk);
    }
    else
    {
        nameOk = false;
    }

    if (!parseOk || !nameOk)
    {
        ui->lblStatus->setText("Bad file name - should start with pos or vw");
        error = -1;
    }



    if (error >= 0 && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            eventManager.addEvent(eventType, userId, line);
        }

        ui->lblStatus->setText(tr ("read %1 file, user id %2").arg(eventType == Event::NavEvent?"locaton":"visit wares").arg(userId));

    }
    else
    {
        qDebug() << "Can't open file " + fileName;
    }

    return error;
}

void MainWindow::switchPause(){
    if(this->pause == false){
        this->pause = true;
    }else if(this->pause == true){
        this->pause = false;
    }
}

