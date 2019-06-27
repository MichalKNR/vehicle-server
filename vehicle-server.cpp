#include "vehicle-server.h"

VehicleServer::VehicleServer()
{
    Zm().vehicleServerObj= (void*)this;
    signal(SIGTERM,terminate_wrapper);
    signal(SIGHUP,reload_wrapper);

    settings = new QSettings(Zm().configPath+Zm().configFile, QSettings::IniFormat);
    qDebug()<<"path:"<<Zm().configPath<<" file:"<<Zm().configFile;
    this->lockFile();
    this->setVariables();
    this->openLogFile();

    QStringList list = settings->allKeys();
    qDebug() << "VehicleServer::VehicleServer printing all settings values";
    for(int i = 0;i < list.count();i++) {
        qDebug() << "VehicleServer::VehicleServer config key:" << list.at(i)<<" val:" << settings->value(list.at(i));
    }
    appNetManager = new AppNetManager(this);

    appMgr = new AppMgr(this);

    qRegisterMetaType<QDomDocument>("QDomDocument");
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

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

void VehicleServer::lockFile() {
    char str[10];
    int lfp=open(Zm().lockFile.toLatin1(),O_RDWR|O_CREAT,0640);
    if (lfp<0) {
        qCritical()<<"Can't open lock file "<<Zm().lockFile<<": "<<strerror(errno); /* can not open */
        exit(1);
    }
    if (lockf(lfp,F_TLOCK,0)<0) {
        qCritical()<<"Can't create lock file "<<Zm().lockFile<<": "<<strerror(errno); /* can not lock */
        exit(1);
    }
    QCoreApplication::applicationPid();
    sprintf(str,"%d\n",QCoreApplication::applicationPid());
    write(lfp,str,strlen(str));
}

void VehicleServer::setVariables() {
    Zm().logFileName = settings->value("logFileName").toString();
    Zm().appListenPort = settings->value("appListenPort").toInt();
    Zm().devListenPort = settings->value("devListenPort").toInt();
    Zm().logging = settings->value("logging").toInt();
    Zm().logLevel = settings->value("logLevel").toInt();
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

void terminate_wrapper(int dummy) {
    VehicleServer *listekServer=(VehicleServer*)Zm().vehicleServerObj;
    listekServer->terminate(true);
}

void reload_wrapper(int dummy) {
    qDebug()<<"1 reload from SIGHUP";
    VehicleServer *saratServer=(VehicleServer*)Zm().vehicleServerObj;
    saratServer->reload();
}

void VehicleServer::terminate(bool fromSignal) {
    qDebug()<<"1 SaratServer::terminate from signal:"<<fromSignal;
    qApp->quit();
}

void VehicleServer::reload() {
    settings->sync();
    Zm().logging=settings->value("logging").toInt();
    Zm().logLevel=settings->value("logLevel").toInt();
    this->openLogFile();
}
