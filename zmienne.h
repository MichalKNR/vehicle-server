#ifndef ZMIENNE_H
#define ZMIENNE_H

#include <QtCore>
#include <QObject>


class Singleton {
// definicja klasy o nazwie Singleton - jest
// to nazwa wlasna :)
public:
        QString mainPath;
        QString configPath;
        QString configFile;
        QString projectFile;
        int     appListenPort;
        int     devListenPort;
        int     logging;
        int     logLevel;
        QFile   logFile;
        QString logFileName;
        QString lockFile;
        QLocale locale;

        int listenPort;
private:
        Singleton();
        Singleton(const Singleton&);
        // konstruktor klasy

        friend Singleton& Zm();
};

Singleton& Zm();

#endif // ZMIENNE_H
