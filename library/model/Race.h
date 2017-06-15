#pragma once

#include <QString>

#include "libtelemetry_export.h"

class LIBTELEMETRY_EXPORT Race
{
    private:
        int ID;

        QString Name;
        QString Description;
        QString Weather;
        QString Date;


    public:
        Race();

        int GetID();
        QString GetName();
        QString GetDescription();
        QString GetWeather();
        QString GetDate();

        //set text
        void SetID(int ID);
        void SetName(QString name);
        void SetDescription(QString description);
        void SetWeather(QString weather);
        void SetDate(QString date);
};
