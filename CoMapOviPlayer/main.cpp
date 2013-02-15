#include <QtGui/QApplication>
#include "mainwindow.h"
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"
#include <QDebug>
#include <QDesktopWidget>
#include <qgeoserviceproviderfactory.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QRect screenSize(QApplication::desktop()->rect().topLeft(), QApplication::desktop()->rect().bottomRight());
    MappingWidget mapWidget (screenSize);

   // QList<QGeoServiceProviderFactory*> candidates = QGeoServiceProviderPrivate::plugins().values("nokia");

    QGeoServiceProvider serviceProvider ("nokia");

    if (serviceProvider.error() == QGeoServiceProvider::NoError)
    {
        mapWidget.initialize(serviceProvider.mappingManager());
    }
    else
    {
        qDebug() << "Service provider error: " << serviceProvider.errorString();
    }

    w.addMapWidget(&mapWidget);
    w.showMaximized();

    return a.exec();
}
