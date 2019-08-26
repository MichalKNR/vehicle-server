#include "app-net-thread.h"
#include "zmienne.h"

AppNetThread::AppNetThread(int client_id,int socketDescriptor,QObject *parent): QThread(parent), socketDescriptor(socketDescriptor) {
    this->client_id=client_id;

    qDebug()<<"11 AppNetThread::AppNetThread starting thread for client_id:"<<client_id;
    socket=new QTcpSocket();
    if(!socket->setSocketDescriptor(socketDescriptor)) {
        qCritical()<<"AppNetThread::AppNetThread client_id:"<<client_id<<" setSocketError:"<<socket->error();
        return;
    }
    requestSize=0;

    connect(socket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this,SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(socketError(QAbstractSocket::SocketError)));
}
void AppNetThread::sendToApp(QJsonDocument doc) {
    this->writeToSocket(doc);
}
void AppNetThread::closeApp() {
    qDebug()<<"AppNetThread::closeApp";
    socket->disconnectFromHost();
}
void AppNetThread::writeToSocket(QJsonDocument doc) {
    QString text = doc.toJson();
    QByteArray block;
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint32)0;
    out << text;
    out.device()->seek(0);
    out << (quint32)(block.size() - sizeof(quint32));

    if(!socket->write(block)) {
        qWarning()<<"AppNetThread::writeToSocket client_id:"<<client_id<<" failed xml:"<<doc.toJson();
    } else {
        qDebug().noquote()<<"8 AppNetThread::writeToooSocket client_id:"<<client_id<<" json"<<doc.toJson();
    }
}

void AppNetThread::sendPong() {
    QJsonObject obj;
    obj.insert("type", QJsonValue::fromVariant("pong"));
    writeToSocket(QJsonDocument(obj));
}
QString AppNetThread::getPeerAddr() {
    return socket->peerAddress().toString();
}
void AppNetThread::closeClient() {
    qDebug()<<"4 AppNetThread::closeClient client_id:"<<client_id;
    socket->deleteLater();
    emit clientClosed(client_id);
    this->quit();
}
void AppNetThread::socketStateChanged(QAbstractSocket::SocketState state) {
    switch(state) {
    case QAbstractSocket::UnconnectedState:
        qDebug() <<"8 AppNetThread::socketStateChanged state=unconnected client_id:"<<client_id;
        this->closeClient();
        break;
    case QAbstractSocket::HostLookupState:
        qDebug() <<"8 AppNetThread::socketStateChanged state=host lookup client_id:"<<client_id;
        break;
    case QAbstractSocket::ConnectingState:
        qDebug() <<"8 AppNetThread::socketStateChanged state=connecting client_id:"<<client_id;
        break;
    case QAbstractSocket::ConnectedState:
        qDebug() <<"8 AppNetThread::socketStateChanged state=connected client_id:"<<client_id;
        break;
    case QAbstractSocket::ClosingState:
        qDebug() <<"8 AppNetThread::socketStateChanged state=closing connection client_id:"<<client_id;
        break;
    }
}
void AppNetThread::socketError(QAbstractSocket::SocketError error) {
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() <<"8 AppNetThread::socketError error=remote host closed connection client_id:"<<client_id;
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() <<"8 AppNetThread::socketError error=host not found client_id:"<<client_id;
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() <<"8 AppNetThread::socketError error=connection refused client_id:"<<client_id;
        break;
    default:
        qDebug() <<"8 AppNetThread::socketError client_id:"<<client_id<<" error:"<<socket->errorString();
    }
}
