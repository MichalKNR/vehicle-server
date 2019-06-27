#include "app-mgr.h"
#include "zmienne.h"
#include "helper.h"

AppMgr::AppMgr(QObject *parent):QObject(parent) {

}

void AppMgr::clientClosed(int app_client_id) {
    qDebug() << "client " << app_client_id << " disconnected TODO what to do now";
}

void AppMgr::clientConnected(int client_id) {
    qDebug() << "AppMgr::clientConnected";
    // send All data
    QJsonDocument doc = Helper::createSpeedJson(valueSpeed);
    emit sendToApp(client_id, doc);

    doc = Helper::createSteerTemperatureJson(valueSteerTemperature);
    emit sendToApp(client_id, doc);

    doc = Helper::createSteerAccurancyJson(valueSteerAccurancy);
    emit sendToApp(client_id, doc);

    doc = Helper::createEngineTemperatureJson(valueEngineTemperature);
    emit sendToApp(client_id, doc);

    doc = Helper::createEngineAccurancyJson(valueEngineAccurancy);
    emit sendToApp(client_id, doc);

    doc = Helper::createBatteryTemperatureJson(valueBatteryTemperature);
    emit sendToApp(client_id, doc);

    doc = Helper::createBatteryAccurancyJson(valueBatteryAccurancy);
    emit sendToApp(client_id, doc);

    doc = Helper::createBatteryPercentJson(valueBatteryPercent);
    emit sendToApp(client_id, doc);

    doc = Helper::createUnderLightsOnJson(valueUnderLightsOn);
    emit sendToApp(client_id, doc);

    doc = Helper::createCheckEngineOnJson(valueCheckEngineOn);
    emit sendToApp(client_id, doc);

    doc = Helper::createAlarmOnJson(valueAlarmOn);
    emit sendToApp(client_id, doc);

}



