#pragma once

#include <QObject>

#include "libtelemetry_export.h"

#include "library/model/Race.h"
#include "library/model/Record.h"
#include "library/network/NetworkClient.h"

class LIBTELEMETRY_EXPORT ServerClient : public QObject
{
    Q_OBJECT

private:
    explicit ServerClient(QObject* parent = 0);
    static ServerClient* createInstance();

    NetworkClient* nc;


public:
    ~ServerClient();
    static ServerClient* instance();

    bool CreateRace(Race* race);
    bool CreateRecord(Race* race, Record* record);
};
