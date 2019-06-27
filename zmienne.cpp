#include "zmienne.h"

Singleton::Singleton() {
    // konstruktor klasy - nie używany :))
    mainPath=QString("%1/").arg(QDir::currentPath());
    configPath=mainPath+"config/";
    configFile="vehicle-server.conf";
    projectFile="project.xml";
    lockFile="/tmp/vehicle-server.lock";
    locale=QLocale("pl_PL");
    skip_counter_number=1;
    protocol_count=10;
}

Singleton& Zm() {
// funkcja glowna singletonu
        static Singleton zmienne;
        return zmienne;
}
