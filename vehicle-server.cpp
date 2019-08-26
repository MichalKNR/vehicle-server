#include "vehicle-server.h"

VehicleServer::VehicleServer()
{
    QString configFileName = "vehicle-server.conf";
    settings = new QSettings(configFileName, QSettings::IniFormat);

    if (QFileInfo::exists(configFileName) && QFileInfo(configFileName).isFile()) {
        qDebug() << "VehicleServer::VehicleServer read configFile " << configFileName;

        QString key = "listenPort";
        if (settings->contains(key)) {
            Zm().listenPort = settings->value(key).toInt();
        } else {
            qDebug() << "VehicleServer::VehicleServer config file does not contains " << key;
        }

        key = "logFileName";
        if (settings->contains(key)) {
            Zm().logFileName = settings->value("logFileName").toString();
        } else {
            qDebug() << "VehicleServer::VehicleServer config file does not contains " << key;
        }

    } else {
        qDebug() << "VehicleServer::VehicleServer configFile " << configFileName << " not found";
    }


    this->openLogFile();

    QStringList list = settings->allKeys();
    qDebug() << "VehicleServer::VehicleServer printing all settings values";
    for(int i = 0;i < list.count();i++) {
        qDebug() << "VehicleServer::VehicleServer config key:" << list.at(i)<<" val:" << settings->value(list.at(i));
    }

    appNetManager = new AppNetManager(this);
    appMgr = new AppMgr(this);

    //connections

    //from appNetManager
    connect(appNetManager,SIGNAL(clientClosed(int)),appMgr,SLOT(clientClosed(int)));
    connect(appNetManager,SIGNAL(clientConnected(int)),appMgr,SLOT(clientConnected(int)));

    //to appNetManager
    connect(appMgr,SIGNAL(sendToApp(int,QJsonDocument)),appNetManager,SLOT(sendToApp(int,QJsonDocument)));
    connect(appMgr,SIGNAL(sendToAll(QJsonDocument)),appNetManager,SLOT(sendToAll(QJsonDocument)));


    //from devNetManager

    appNetManager->init();

    qDebug()<<"VehicleServer::VehicleServer all main objects intialized";

}

void VehicleServer::openLogFile() {
    if(!Zm().logging) {
        if(Zm().logFile.isOpen()) {
            QString msg("Debug: %1 Log closed\n");
            msg=msg.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            Zm().logFile.write(msg.toLatin1().data());
            Zm().logFile.close();
        }
        return;
    }
    if(Zm().logFileName.isEmpty())
        return;
    if(Zm().logFile.isOpen()) {
        Zm().logFile.close();
    }
    Zm().logFile.setFileName(Zm().logFileName);
    Zm().logFile.open(QIODevice::Append | QIODevice::Text | QIODevice::Unbuffered);
    QString msg("Debug: %1 Log opened\n");
    msg=msg.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    Zm().logFile.write(msg.toLatin1().data());
}
