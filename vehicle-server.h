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
private:
    void openLogFile();
private:
    QSettings       *settings;
    AppNetManager   *appNetManager;
    AppMgr          *appMgr;

};
#endif // LISTEKSERVER_H
