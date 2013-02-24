#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventmanager.h"

class MappingWidget;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const QString NOT_CONNECTED_TEXT;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addMapWidget(MappingWidget* mapWidget);
    inline MappingWidget* getMapWidget() {return this->mapWidget;}



private slots:
    void loadIcons();
    void clearMapObjects();
    int loadDataLog();
    void startPlayback();
    void switchPause();
    void sliderAdjusted();
    void playPressed();
    void tracerRedSwitched();
    void tracerBlueSwitched();


private:
    Ui::MainWindow *ui;
    MappingWidget* mapWidget;
    EventManager eventManager;
    bool pause;
    int currAction;
    int totalActions;
    int actionsLeft;
    void updateUi();
    void processEvent(Event* event);
    void updateMap(QGeoBoundingBox box, int userId);
    void updateAnchors(QGeoCoordinate pos, int userId);
    void sleepFor(int timeToWait);
    void sendVLCHotkey();
    void sendVLCPauseHotkey();
    bool tracerRedState;
    bool tracerBlueState;



};

#endif // MAINWINDOW_H
