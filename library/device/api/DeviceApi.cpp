#include "DeviceApi.h"

QList<QString> DeviceApi::GetApiVersions()
{
    return QList<QString>{"v1"};
}

void DeviceApi::SetApiVersion(QString str)
{
   //DeviceApi::apiVersion=str;
}
