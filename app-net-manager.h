#ifndef APPNETMANAGER_H
#define APPNETMANAGER_H

#include <QtNetwork>
#include "app-net-thread.h"

struct AppClientStruct {
    int client_id;
    AppNetThread *thread;
};

class AppNetManager : public QTcpServer
 {
     Q_OBJECT

 public:
     AppNetManager(QObject *parent);
 public slots:
     void init();
     void sendToApp(int client_id,QJsonDocument);
     void sendToAll(QJsonDocument);
     void closeApp(int client_id);
 protected:
     void incomingConnection(qintptr socketDescriptor);
 signals:
     void clientClosed(int client_id);
     void clientConnected(int client_id);
 private slots:
     void deleteClient(int client_id);
 private:
    QMap<int,AppClientStruct*> clientMap;
    int     clientId;
 };

#endif // APPNETMANAGER_H
