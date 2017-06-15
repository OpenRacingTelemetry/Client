#pragma once

#include "library/weather/METAR.h"
#include "library/weather/TAF.h"

class Weather
{
private:
    TAF weatherForecast;
    METAR weatherCurrent;
    QString comments;
public:
    Weather();
    Weather(QString comments);

    QString GetComments();
};
