#ifndef APPNETTHREAD_H
#define APPNETTHREAD_H

#include <QThread>
#include <QAbstractSocket>
#include <qabstractsocket.h>
#include <QTcpSocket>
#include <qtcpsocket.h>
#include <QHostAddress>
#include <QDateTime>
#include <QtXml/QDomDocument>
#include <QQueue>
#include <QJsonObject>
#include <QJsonDocument>

class AppNetThread : public QThread
{
    Q_OBJECT

public:
    AppNetThread(int client_id,int socketDescriptor,QObject *parent);
public slots:
    QString getPeerAddr();
    void sendToApp(QJsonDocument);
    void closeApp();
signals:
    void newAppMgrReq(int client_id, QJsonDocument doc);
    void clientClosed(int client_id);
    void sendDebug(int code,QString msg);
private slots:
    void writeToSocket(QJsonDocument doc);
    void socketStateChanged(QAbstractSocket::SocketState state);
    void socketError(QAbstractSocket::SocketError error);
    void closeClient();
    void sendPong();
private:
    int                client_id;
    int                socketDescriptor;
    QTcpSocket          *socket;
    quint32            requestSize;
};

#endif // APPNETTHREAD_H
