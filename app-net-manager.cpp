#include "app-net-manager.h"
#include "zmienne.h"

AppNetManager::AppNetManager(QObject *parent): QTcpServer(parent) {
    this->clientId=0;
}
void AppNetManager::init() {
    this->listen(QHostAddress::Any,Zm().listenPort);
    qDebug() << "AppNetManager::init listen on " << Zm().listenPort;
}

void AppNetManager::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "AppNetManager::incomingConnection";
    clientId++;
    AppClientStruct *client = new AppClientStruct;
    client->client_id = clientId;
    client->thread = new AppNetThread(client->client_id,socketDescriptor,this);

    connect(client->thread,SIGNAL(clientClosed(int)),this,SLOT(deleteClient(int)));
    client->thread->start();
    clientMap.insert(client->client_id,client);
    qDebug() << "emit now";
    emit clientConnected(client->client_id);
}
void AppNetManager::deleteClient(int client_id) {
    qDebug() << "6 AppNetManager::deleteClient client_id:"<<client_id;
    clientMap[client_id]->thread->exit();
    clientMap[client_id]->thread->wait();
    clientMap[client_id]->thread->deleteLater();
    delete clientMap[client_id];
    clientMap.remove(client_id);
    emit clientClosed(client_id);
}

void AppNetManager::sendToApp(int client_id, QJsonDocument doc) {
    if(!clientMap.contains(client_id)) {
        qWarning()<<"AppNetManager::sendToApp there is no client_id:"<<client_id;
        return;
    }
    clientMap[client_id]->thread->sendToApp(doc);
}

void AppNetManager::sendToAll(QJsonDocument doc) {
    for (auto client: clientMap) {
        client->thread->sendToApp(doc);
    }
}

void AppNetManager::closeApp(int client_id) {
    if(!clientMap.contains(client_id)) {
        qWarning()<<"AppNetManager::closeApp there is no client_id:"<<client_id;
        return;
    }
    clientMap[client_id]->thread->closeApp();
}
