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
#include "event.h"

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
    connect(ui->loadVw1, SIGNAL(clicked()), this, SLOT(loadDataLog()));
    connect(ui->btnPlay, SIGNAL(clicked()), this, SLOT(startPlayback()));
    connect(ui->btnPause, SIGNAL(clicked()), this, SLOT(switchPause()));
    connect(ui->horizontalSlider, SIGNAL(sliderReleased()), this, SLOT(sliderAdjusted()));
    connect(ui->horizontalSlider, SIGNAL(sliderPressed()), this, SLOT(switchPause()));


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
    //set played and remaining

    int timeToWait;
    QTime currTime;
    QTime nextTime;

    Event* currEvent;
    Event* nextEvent;

    //check if the file has been loaded
    updateUi();

    if(eventManager.isInicialized() && currAction < totalActions){
         qDebug()<< "Playback started";
         ui->lblStatus->setText("Playback started");
         qDebug("Current action: %d",currAction);

         //refactor this
         currEvent = eventManager.getEventAt(currAction);
         currAction++;
         currTime = currEvent->getTime();
         //refactor this


         nextEvent = eventManager.getEventAt(currAction);
         currAction++;
         nextTime = nextEvent->getTime();
         updateUi();

         timeToWait = abs(nextTime.msecsTo(currTime));
         qDebug("value = %d", timeToWait);

         processEvent(currEvent);

         //sleeping for x msecs
         sleepFor(timeToWait);

         processEvent(nextEvent);

         currEvent = nextEvent;


         while(eventManager.getLength() > currAction && pause == false){


            nextEvent = eventManager.getEventAt(currAction);
            currAction++;

            currTime = currEvent->getTime();
            nextTime = nextEvent->getTime();
            timeToWait = abs(nextTime.msecsTo(currTime));
            qDebug("value = %d", timeToWait);

            processEvent(currEvent);

            //sleeping for x msecs
            sleepFor(timeToWait);

            processEvent(nextEvent);

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

void MainWindow::processEvent(Event* event){
    if(event->getType() == Event::NavEvent){
        updateMap(event->getBox(), event->getUserId());
    }else if(event->getType() == Event::AnchorEvent){
        updateAnchors(event->getPos(), event->getUserId());
    }
}

void MainWindow::updateUi(){
    QString numSteps;
    actionsLeft = totalActions-currAction;
    ui->lblNumSteps->setText(numSteps.setNum(actionsLeft));
    ui->horizontalSlider->setSliderPosition(currAction);

}

void MainWindow::updateMap(QGeoBoundingBox box, int userId){
    mapWidget->mapBoxChanged(box,userId);
    mapWidget->update();
    updateUi();
}

void MainWindow::updateAnchors(QGeoCoordinate pos, int userId){
    mapWidget->mapAnchorAdded(pos,userId);
    mapWidget->update();
    updateUi();
}

void MainWindow::sleepFor(int timeToWait){
    //sleeping for x msecs
    QTimer timer;
    timer.start(timeToWait);
    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    loop.exec();
}

void MainWindow::sliderAdjusted(){
    int positionDebug = ui->horizontalSlider->sliderPosition();
    this->currAction = positionDebug;
    startPlayback();
}

void MainWindow::loadIcons()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("CSV files (*.csv)"));
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
    ui->lblStatus->setText("");
    ui->lblNumSteps->setText("");
    ui->Log1loaded->setChecked(false);
    ui->Log2loaded->setChecked(false);
}

int MainWindow::loadDataLog()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text files (*.txt)")); //seqfaults here when loading another file
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
        if(userId == 0){
            ui->Log1loaded->setChecked(true);
        }else if (userId == 1){
            ui->Log2loaded->setChecked(true);
        }
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
        file.close();
    }
    else
    {
        qDebug() << "Can't open file " + fileName;
    }


    //in case a file has been played before

    currAction=0;
    totalActions=0;
    actionsLeft = 0;
    pause = false;


    return error;
}

void MainWindow::switchPause(){
    if(this->pause == false){
        this->pause = true;
    }else if(this->pause == true){
        this->pause = false;
        startPlayback();
    }
}

