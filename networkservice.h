#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QJsonObject>
#include <functional>
#include <QHash>

class NetworkService : public QObject {
    Q_OBJECT

public:
    static NetworkService& instance();

    void post(const QString& endpoint, const QJsonObject& json);
    void get(const QString& endpoint, std::function<void(const QJsonArray&)> callback);
    void patch(const QString& endpoint); // no body
    void patch(const QString& endpoint, const QJsonObject& json); // with body
    void del(const QString& endpoint);

private:
    explicit NetworkService();
    QNetworkAccessManager* manager;
    QHash<QNetworkReply*, std::function<void(const QJsonArray&)>> callbackMap;

private slots:
    void onReplyFinished(QNetworkReply* reply);
};

#endif // NETWORKSERVICE_H
