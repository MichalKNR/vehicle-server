#ifndef LISTEKSERVER_H
#define LISTEKSERVER_H

#include <QTimer>
#include <QThread>
#include <QtCore/QFile>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "zmienne.h"
#include "signal.h"
#include "app-net-manager.h"
#include "app-mgr.h"


class VehicleServer: public QObject
{
    Q_OBJECT
public:
    VehicleServer();
public slots:
    void terminate(bool fromSignal=false);
    void reload();
private slots:
    void lockFile();
    void setVariables();
    void openLogFile();
private:
    QSettings       *settings;
    QSettings       *sslSettings;
    AppNetManager   *appNetManager;
    AppMgr          *appMgr;

};

extern "C" void terminate_wrapper(int dummy);
extern "C" void reload_wrapper(int dummy);
#endif // LISTEKSERVER_H
