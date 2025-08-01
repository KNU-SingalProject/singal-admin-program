#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QNetworkReply>

class NetworkService : public QObject
{
    Q_OBJECT

private:
    NetworkService();
    QNetworkAccessManager* manager;

public:
    static NetworkService& instance();

    void post(const QString& endpoint, const QJsonObject& json);
    void get(const QString& endpoint, std::function<void(const QJsonArray&)> callback);

private slots:
    void onReplyFinished(QNetworkReply* reply);

private:
    std::function<void(const QJsonArray&)> currentCallback;
};

#endif // NETWORKSERVICE_H
