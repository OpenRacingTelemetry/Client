#include "ServerClient.h"

#include "library/common/Config.h"
#include "library/common/Singleton.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>


ServerClient::ServerClient(QObject* parent): QObject(parent)
{
    nc = NetworkClient::instance();
}


ServerClient* ServerClient::createInstance()
{
    return new ServerClient();
}

ServerClient::~ServerClient()
{
}

ServerClient* ServerClient::instance()
{
    return Singleton<ServerClient>::instance(ServerClient::createInstance);
}

bool ServerClient::CreateRace(Race* race)
{
    if(race->GetID()!=-1)
    {
        return true;
    }

    QJsonObject jsonobj;
    jsonobj["Name"]=race->GetName();
    jsonobj["Description"]=race->GetDescription();
    jsonobj["Date"]=race->GetDate();
    jsonobj["Weather"]=race->GetWeather();
    QJsonDocument doc(jsonobj);

    QEventLoop eventLoop;
    QNetworkReply* resp = nc->SendPostRequest(QUrl("http://localhost:58614/api/races"),doc.toJson(),"application/json");
    QObject::connect(nc, NetworkClient::finished, &eventLoop, QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = resp->readAll();
    QString strReply = QString::fromUtf8(bytes.data(), bytes.size());
    QJsonObject jsonObject = QJsonDocument::fromJson(strReply.toUtf8()).object();

    if(!jsonObject.contains("raceId"))
    {
        return false;
    }

    race->SetID(jsonObject["raceId"].toInt());

    return true;
}


bool ServerClient::CreateRecord(Race* race, Record* record)
{
    if(race->GetID()==-1)
    {
        return false;
    }

    QJsonObject jsonobj;
    jsonobj["RaceId"]=QString::number(race->GetID());
    jsonobj["TimeStart"]=record->GetTimeStart().toString("HH:mm:ss.zzz");
    jsonobj["TimeEnd"]=record->GetTimeEnd().toString("HH:mm:ss.zzz");
    jsonobj["TimePenalty"]=record->GetTimePenalty().toString("HH:mm:ss.zzz");
    jsonobj["Notes"]=record->GetNotes();
    QJsonDocument doc(jsonobj);

    QEventLoop eventLoop;

    QString url = QString("http://localhost:58614/api/races/")+QString::number(race->GetID());

    QNetworkReply* resp = nc->SendPostRequest(QUrl(url),doc.toJson(),"application/json");
    QObject::connect(nc, NetworkClient::finished, &eventLoop, QEventLoop::quit);
    eventLoop.exec();

    QByteArray bytes = resp->readAll();
    QString strReply = QString::fromUtf8(bytes.data(), bytes.size());
    QJsonObject jsonObject = QJsonDocument::fromJson(strReply.toUtf8()).object();

    if(!jsonObject.contains("id"))
    {
        return false;
    }

    record->SetID(jsonObject["id"].toInt());

    return true;
}

