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

private:
    Ui::MainWindow *ui;
    MappingWidget* mapWidget;
    EventManager eventManager;
    int currAction;
    int totalActions;
    int actionsLeft;
    void updateUi();
    void updateMap();

};

#endif // MAINWINDOW_H
