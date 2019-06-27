#ifndef APPMGR_H
#define APPMGR_H

#include <QtCore>



class AppMgr:public QObject {
    Q_OBJECT
public:
    AppMgr(QObject *parent);

public slots:
    void clientClosed(int app_client_id);
    void clientConnected(int client_id);

signals:
    void sendToApp(int app_client_id,QJsonDocument);
    void sendToAll(QJsonDocument);
private slots:    

private:

    int valueSpeed = 130;
    int valueSteerTemperature = 20;
    int valueSteerAccurancy = 2;
    int valueEngineTemperature = 31;
    int valueEngineAccurancy = 12;
    int valueBatteryTemperature = 13;
    int valueBatteryAccurancy = 1;
    int valueBatteryPercent = 40;

    bool valueUnderLightsOn = false;
    bool valueCheckEngineOn = false;
    bool valueAlarmOn = false;

};

#endif // APPMGR_H
