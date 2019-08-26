#include <QCoreApplication>
#include <iostream>
#include "zmienne.h"
#include "vehicle-server.h"

void logMsg(QString msg) {
    if(!Zm().logFileName.isEmpty() && Zm().logFile.isOpen())
        Zm().logFile.write(msg.toLatin1().data());
    else
        fprintf(stderr, msg.toLatin1().data());
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QString string=QString("%1 %2\n").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(msg);
    switch (type) {
    case QtDebugMsg:
        string.prepend("Debug: ");
        logMsg(string);
        break;
    case QtWarningMsg:
        string.prepend("Warning: ");
        logMsg(string);
        break;
    case QtCriticalMsg:
        string.prepend("Critical: ");
        logMsg(string);
        break;
    case QtFatalMsg:
        string.prepend("Fatal: ");
        logMsg(string);
        abort();
    }
}

int main(int argc, char *argv[])
{
    try {
        qInstallMessageHandler(myMessageOutput);
        QCoreApplication a(argc, argv);

        QLocale::setDefault(QLocale::English);

        VehicleServer vehicleServer;
        return a.exec();
    } catch(const std::bad_alloc &) {
        logMsg(QString("out of memory error"));
        std::cout<<"out of memory error";
    }
}
