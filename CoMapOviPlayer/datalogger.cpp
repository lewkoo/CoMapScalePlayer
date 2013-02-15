//#include "datalogger.h"
//#include <QDir>
//#include <QDebug>
//#include <QDateTime>


//const QString DataLogger::LOG_PATH = "DataLogs";
//const char DataLogger::DELIM = ';';

//DataLogger::DataLogger(QString clientId)
//{
//    this->clientId = clientId;
//    createFiles();
//}

//void DataLogger::createFiles()
//{
//    QDir folder(DataLogger::LOG_PATH);
//    QString fileName;

//    if (!folder.exists())
//    {
//        bool folderMade = QDir::current().mkdir(DataLogger::LOG_PATH);

//        if (!folderMade)
//        {
//            qDebug() << "Can't make directory " + DataLogger::LOG_PATH;
//        }
//    }

//    //Create file to log positions
//    fileName = folder.path() + "/Pos_Log-Client_" + clientId + "_" + QDateTime::currentDateTime().toString() + ".txt";
//    posFile.setFileName(fileName);

//    if (!posFile.open(QIODevice::WriteOnly))
//    {
//        qDebug() << "Can't open file " + fileName;
//    }

//    posFileOut.setDevice(&posFile);

//    //Create file to log visit wears
//    fileName = folder.path() + "/Vw_Log-Client_" + clientId + "_" + QDateTime::currentDateTime().toString() + ".txt";
//    vwFile.setFileName(fileName);

//    if (!vwFile.open(QIODevice::WriteOnly))
//    {
//        qDebug() << "Can't open file " + fileName;
//    }

//    vwFileOut.setDevice(&vwFile);
//}

//void DataLogger::writePos(QString time, QString lat, QString lon, QString topLeftLat, QString topLeftLon, QString botRightLat, QString botRightLon, QString scale)
//{
//    QString text = time + DELIM + lat + DELIM + lon + DELIM + topLeftLat + DELIM + topLeftLon + DELIM + botRightLat + DELIM + botRightLon + DELIM + scale;
//    posFileOut << text << endl;
//}

//void DataLogger::writeVw(QString time, QString lat, QString lon, QString topLeftLat, QString topLeftLon, QString botRightLat, QString botRightLon, QString scale)
//{
//    QString text = time + DELIM + lat + DELIM + lon + DELIM + topLeftLat + DELIM + topLeftLon + DELIM + botRightLat + DELIM + botRightLon + DELIM + scale;
//    vwFileOut << text << endl;
//}

//void DataLogger::closeFiles()
//{
//    posFileOut.flush();
//    posFile.flush();
//    posFile.close();

//    vwFileOut.flush();
//    vwFile.flush();
//    vwFile.close();
//}
