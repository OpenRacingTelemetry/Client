#include "Race.h"

Race::Race()
{
    this->Date="01.01.0001";
    this->ID=-1;
}

int Race::GetID()
{
    return this->ID;
}

QString Race::GetName()
{
    return this->Name;
}

QString Race::GetDescription()
{
    return this->Description;
}

QString Race::GetWeather()
{
    return this->Weather;
}

QString Race::GetDate()
{
    return this->Date;
}

void Race::SetID(int ID)
{
    this->ID = ID;
}

void Race::SetName(QString name)
{
    this->Name=name;
}

void Race::SetDescription(QString description)
{
    this->Description=description;
}

void Race::SetWeather(QString weather)
{
    this->Weather = weather;
}

void Race::SetDate(QString date)
{
    this->Date = date;
}
