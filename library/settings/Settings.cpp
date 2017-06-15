#include "Settings.h"

template <typename T>
void Settings::SetSetting(QString key, T value)
{
    settings->setValue(key,value);
}

template <typename T>
T Settings::GetSetting(QString key)
{
    return settings->value(key);
}

Settings::Settings() {
    settings = new QSettings("RFCT_TEAM","Telemetry");

}

Settings::~Settings() {
    delete settings;
}
