#include "networkservice.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

NetworkService::NetworkService() {
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &NetworkService::onReplyFinished);
}

NetworkService& NetworkService::instance() {
    static NetworkService instance;
    return instance;
}

void NetworkService::post(const QString& endpoint, const QJsonObject& json) {
    QNetworkRequest request(QUrl("http://43.201.162.230:8000" + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    qDebug() << "[POST]" << endpoint << body;
    manager->post(request, body);
}

void NetworkService::get(const QString& endpoint, std::function<void(const QJsonArray&)> callback) {
    QNetworkRequest request(QUrl("http://43.201.162.230:8000/" + endpoint));
    currentCallback = callback;
    manager->get(request);
}

void NetworkService::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (doc.isArray()) {
        if (currentCallback) currentCallback(doc.array());
    } else {
        qDebug() << "응답 형식이 JSON 배열이 아님:" << responseData;
    }

    reply->deleteLater();
}
