#pragma once

#include <QList>
#include <QString>

class DeviceApi
{
public:
    static QList<QString> GetApiVersions();
    static void SetApiVersion(QString str);
private:
   static QString apiVersion;
};
