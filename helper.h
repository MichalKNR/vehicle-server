#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <memory>
#include <QtCore>

class Helper
{
public:
    Helper();
    static QJsonDocument createSpeedJson(int v);
    static QJsonDocument createSteerTemperatureJson(int v);
    static QJsonDocument createSteerAccurancyJson(int v);
    static QJsonDocument createEngineTemperatureJson(int v);
    static QJsonDocument createEngineAccurancyJson(int v);
    static QJsonDocument createBatteryTemperatureJson(int v);
    static QJsonDocument createBatteryAccurancyJson(int v);
    static QJsonDocument createBatteryPercentJson(int v);

    static QJsonDocument createUnderLightsOnJson(bool on);
    static QJsonDocument createCheckEngineOnJson(bool on);
    static QJsonDocument createAlarmOnJson(bool on);

};

#endif // HELPER_H
