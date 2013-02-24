#-------------------------------------------------
#
# Project created by QtCreator 2011-10-20T09:26:27
#
#-------------------------------------------------

CONFIG += mobility
MOBILITY += location

#Linux
#INCLUDEPATH += "/opt/QtSDK/Desktop/Qt/474/gcc/include/QtMobility/" \

               #"/opt/QtSDK/Desktop/Qt/474/gcc/plugins/geoservices"
               #"/home/bens/Code/Geoservices_nokia/geoservices/nokia"

QT       += core gui\
            network

TARGET = CoMapOviServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mappingwidget.cpp \
    mapoverlay.cpp \
    mapmarker.cpp \
    geomap.cpp \
    zoombuttonitem.cpp \
    datalogger.cpp \
    eventmanager.cpp \
    event.cpp \
    dataplayer.cpp \
    tracer.cpp

HEADERS  += mainwindow.h \
    mappingwidget.h \
    mapoverlay.h \
    mapmarker.h \
    geomap.h \
    zoombuttonitem.h \
    datalogger.h \
    eventmanager.h \
    event.h \
    dataplayer.h \
    tracer.h

FORMS    += mainwindow.ui

OTHER_FILES +=

RESOURCES += \
    Icons.qrc





















