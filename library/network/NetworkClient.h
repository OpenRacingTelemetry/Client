#pragma once

#include <QMap>
#include <QObject>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>

#include "libtelemetry_export.h"

class LIBTELEMETRY_EXPORT NetworkClient : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager manager;

    bool isAuthenticated = false;

    QString tokenLink="";
    QString clientID ="";

    QString token="";

    explicit NetworkClient(QObject* parent = 0);
    static NetworkClient* createInstance();

public:
    ~NetworkClient();
    static NetworkClient* instance();

    void Initialize(QString clientID, QString tokenLink);

    void SendGetRequest(QUrl url);
    QNetworkReply* SendPostRequest(QUrl url, QMap<QString,QString> parameters);
    QNetworkReply* SendPostRequest(QUrl url, QByteArray body, QString mime);


    void DoAuth(QString login, QString password);

    QNetworkAccessManager* GetManager();

signals:
    void authSuccess();
    void authFail(QString msg);

    void finished();
};
