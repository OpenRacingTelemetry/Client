#pragma once

#include <QString>

class Location
{
private:
    QString geoname;
    double lon;
    double lat;
public:
    Location();
    Location(QString loc);

    QString GetGeoname();
};
