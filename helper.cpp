#include "helper.h"

Helper::Helper()
{

}

QJsonDocument Helper::createSpeedJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "Speed");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createSteerTemperatureJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "SteerTemperature");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createSteerAccurancyJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "SteerAccurancy");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createEngineTemperatureJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "EngineTemperature");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createEngineAccurancyJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "EngineAccurancy");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}


QJsonDocument Helper::createBatteryTemperatureJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "BatteryTemperature");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createBatteryAccurancyJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "BatteryAccurancy");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createBatteryPercentJson(int v) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "BatteryPercent");
    obj.insert("value" , v);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createUnderLightsOnJson(bool on) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "UnderLightsOn");
    obj.insert("value" , on);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createCheckEngineOnJson(bool on) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "CheckEngineOn");
    obj.insert("value" , on);
    return QJsonDocument(obj);
}

QJsonDocument Helper::createAlarmOnJson(bool on) {
    QJsonObject obj;
    obj.insert("type", "request");
    obj.insert("valueId", "AlarmOn");
    obj.insert("value" , on);
    return QJsonDocument(obj);
}
