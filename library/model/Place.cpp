#include "Place.h"

Location::Location()
{

}

Location::Location(QString loc)
{
    this->geoname=loc;
}

QString Location::GetGeoname()
{
    return this->geoname;
}
