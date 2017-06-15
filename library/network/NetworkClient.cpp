#include "NetworkClient.h"

#include "library/common/Singleton.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>

NetworkClient::NetworkClient(QObject* parent): QObject(parent)
{
    isAuthenticated=false;
    Initialize("telemetry","http://localhost:58614/connect/token");
    connect(&manager, QNetworkAccessManager::finished,this,NetworkClient::finished);
}


NetworkClient* NetworkClient::createInstance()
{
    return new NetworkClient();
}

NetworkClient::~NetworkClient()
{
}

NetworkClient* NetworkClient::instance()
{
    return Singleton<NetworkClient>::instance(NetworkClient::createInstance);
}

void NetworkClient::Initialize(QString clientID, QString tokenLink)
{
    this->clientID = clientID;
    this->tokenLink = tokenLink;
}

void NetworkClient::SendGetRequest(QUrl url)
{
    QNetworkRequest request(url);
    if(token!="")
    {
      request.setRawHeader(QString("Authorization").toStdString().c_str(),
                           QString("Bearer "+token).toStdString().c_str());
    }
    manager.get(request);
}

QNetworkReply* NetworkClient::SendPostRequest(QUrl url,QMap<QString,QString> parameters)
{
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    if(token!="")
    {
        request.setRawHeader(QString("Authorization").toStdString().c_str(),
                             QString("Bearer "+token).toStdString().c_str());
    }

    QUrlQuery params;

    QMap<QString, QString>::const_iterator i = parameters.constBegin();
    while (i != parameters.constEnd())
    {
        params.addQueryItem(i.key(),i.value());
        ++i;
    }

    return manager.post(request, params.query(QUrl::FullyEncoded).toUtf8());
}

QNetworkReply* NetworkClient::SendPostRequest(QUrl url, QByteArray body, QString mime)
{
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,mime);
    request.setHeader(QNetworkRequest::ContentLengthHeader,QByteArray::number(body.size()));

    if(token!="")
    {
        request.setRawHeader(QString("Authorization").toStdString().c_str(),
                             QString("Bearer "+token).toStdString().c_str());
    }

    return manager.post(request, body);
}

void NetworkClient::DoAuth(QString login, QString password)
{
   QMap<QString,QString> map;
   map.insert("grant_type","password");
   map.insert("username",login);
   map.insert("password",password);

   QNetworkReply* reply = SendPostRequest(tokenLink,map);
   QEventLoop eventLoop;
   QObject::connect(&manager, QNetworkAccessManager::finished, &eventLoop, QEventLoop::quit);
   eventLoop.exec();

   QByteArray bytes = reply->readAll();
   QString strReply = QString::fromUtf8(bytes.data(), bytes.size());

   QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
   QJsonObject jsonObject = jsonResponse.object();

   if(reply->url().toString().contains("connect/token"))
   {
       if(jsonObject.contains("error"))
       {
           emit authFail(jsonObject["error_description"].toString());
           return;
       }

       if(jsonObject.contains("access_token"))
       {
           token=jsonObject["access_token"].toString();
           isAuthenticated=true;
           emit authSuccess();
           return;
       }
   }
}

QNetworkAccessManager *NetworkClient::GetManager()
{
    return &manager;
}

