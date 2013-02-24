/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Feb 24 14:24:47 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QHBoxLayout *layoutPlaybar;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QSlider *horizontalSlider;
    QLabel *lblTime;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QPushButton *btnClear;
    QPushButton *btnLoad;
    QPushButton *btnLoadLogFile;
    QPushButton *loadVw1;
    QLabel *lblStatus;
    QCheckBox *Log1loaded;
    QCheckBox *Log2loaded;
    QCheckBox *tracerRed;
    QCheckBox *tracer2;
    QLabel *lblNumSteps;
    QPushButton *btnQuit;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(825, 506);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        layoutPlaybar = new QHBoxLayout();
        layoutPlaybar->setSpacing(6);
        layoutPlaybar->setObjectName(QString::fromUtf8("layoutPlaybar"));
        btnPlay = new QPushButton(centralWidget);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));

        layoutPlaybar->addWidget(btnPlay);

        btnPause = new QPushButton(centralWidget);
        btnPause->setObjectName(QString::fromUtf8("btnPause"));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        btnPause->setPalette(palette);

        layoutPlaybar->addWidget(btnPause);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        layoutPlaybar->addWidget(horizontalSlider);

        lblTime = new QLabel(centralWidget);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));

        layoutPlaybar->addWidget(lblTime);


        gridLayout->addLayout(layoutPlaybar, 1, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        verticalLayout->addWidget(btnClear);

        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));

        verticalLayout->addWidget(btnLoad);

        btnLoadLogFile = new QPushButton(centralWidget);
        btnLoadLogFile->setObjectName(QString::fromUtf8("btnLoadLogFile"));

        verticalLayout->addWidget(btnLoadLogFile);

        loadVw1 = new QPushButton(centralWidget);
        loadVw1->setObjectName(QString::fromUtf8("loadVw1"));

        verticalLayout->addWidget(loadVw1);

        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setMinimumSize(QSize(150, 50));
        lblStatus->setMaximumSize(QSize(150, 50));

        verticalLayout->addWidget(lblStatus);

        Log1loaded = new QCheckBox(centralWidget);
        Log1loaded->setObjectName(QString::fromUtf8("Log1loaded"));
        Log1loaded->setEnabled(false);
        Log1loaded->setCheckable(true);

        verticalLayout->addWidget(Log1loaded);

        Log2loaded = new QCheckBox(centralWidget);
        Log2loaded->setObjectName(QString::fromUtf8("Log2loaded"));
        Log2loaded->setEnabled(false);
        Log2loaded->setMouseTracking(true);
        Log2loaded->setCheckable(true);
        Log2loaded->setAutoExclusive(false);
        Log2loaded->setTristate(false);

        verticalLayout->addWidget(Log2loaded);

        tracerRed = new QCheckBox(centralWidget);
        tracerRed->setObjectName(QString::fromUtf8("tracerRed"));

        verticalLayout->addWidget(tracerRed);

        tracer2 = new QCheckBox(centralWidget);
        tracer2->setObjectName(QString::fromUtf8("tracer2"));

        verticalLayout->addWidget(tracer2);

        lblNumSteps = new QLabel(centralWidget);
        lblNumSteps->setObjectName(QString::fromUtf8("lblNumSteps"));
        lblNumSteps->setEnabled(true);
        lblNumSteps->setMinimumSize(QSize(150, 50));
        lblNumSteps->setMaximumSize(QSize(150, 50));

        verticalLayout->addWidget(lblNumSteps);

        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));

        verticalLayout->addWidget(btnQuit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 825, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btnPlay->setText(QApplication::translate("MainWindow", "Play", 0, QApplication::UnicodeUTF8));
        btnPause->setText(QApplication::translate("MainWindow", "Pause", 0, QApplication::UnicodeUTF8));
        lblTime->setText(QApplication::translate("MainWindow", "0:00/0:00", 0, QApplication::UnicodeUTF8));
        btnClear->setText(QApplication::translate("MainWindow", "Clear Map", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MainWindow", "Load Icons", 0, QApplication::UnicodeUTF8));
        btnLoadLogFile->setText(QApplication::translate("MainWindow", "Load Data Log ", 0, QApplication::UnicodeUTF8));
        loadVw1->setText(QApplication::translate("MainWindow", "Load Anchors", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QString());
#ifndef QT_NO_TOOLTIP
        Log1loaded->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        Log1loaded->setText(QApplication::translate("MainWindow", "Log 1 loaded", 0, QApplication::UnicodeUTF8));
        Log1loaded->setShortcut(QString());
        Log2loaded->setText(QApplication::translate("MainWindow", "Log 2 Loaded", 0, QApplication::UnicodeUTF8));
        Log2loaded->setShortcut(QString());
        tracerRed->setText(QApplication::translate("MainWindow", "Tracer User 1 Enabled", 0, QApplication::UnicodeUTF8));
        tracer2->setText(QApplication::translate("MainWindow", "Tracer User 2 Enabled", 0, QApplication::UnicodeUTF8));
        lblNumSteps->setText(QString());
        btnQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
