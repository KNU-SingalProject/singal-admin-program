#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>

class NetworkService : public QObject
{
    Q_OBJECT

private:
    NetworkService();
    QNetworkAccessManager* manager;

public:
    static NetworkService& instance();

    void post(const QString& endpoint, const QJsonObject& json);;
};

#endif // NETWORKSERVICE_H
