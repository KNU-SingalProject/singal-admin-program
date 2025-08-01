#include "networkservice.h"
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QDebug>

NetworkService::NetworkService() {
    manager = new QNetworkAccessManager(this);
}

NetworkService& NetworkService::instance() {
    static NetworkService instance;
    return instance;
}

void NetworkService::post(const QString& endpoint, const QJsonObject& json) {
    QNetworkRequest request(QUrl("http://your.api.server" + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    qDebug() << "[POST]" << endpoint << body;
    manager->post(request, body);
}
