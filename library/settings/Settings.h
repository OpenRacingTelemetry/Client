#pragma once

#include <QSettings>

#include "libtelemetry_export.h"

class LIBTELEMETRY_EXPORT Settings
{
public:
    static Settings& Instance()
    {
        static Settings singleton;
        return singleton;
    }

    template <typename T>
    void SetSetting(QString key,T value);

    template <typename T>
    T GetSetting(QString key);

private:
  Settings();
  ~Settings();

  Settings(const Settings&);                 // Prevent copy-construction
  Settings& operator=(const Settings&);      // Prevent assignment

  QSettings* settings;
};
