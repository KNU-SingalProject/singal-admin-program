#include "networkservice.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
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
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    qDebug() << "[POST]" << endpoint << body;
    manager->post(request, body);
}

void NetworkService::get(const QString& endpoint, std::function<void(const QJsonArray&)> callback) {
    QUrl url("http://43.201.162.230:8000" + endpoint);
    QNetworkRequest request(url);

    qDebug() << "[GET]" << url;

    QNetworkReply* reply = manager->get(request);
    callbackMap[reply] = callback;
}

void NetworkService::patch(const QString& endpoint) {
    QUrl url("http://43.201.162.230:8000" + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    qDebug() << "[PATCH - NO BODY]" << url.toString();

    QNetworkReply* reply = manager->sendCustomRequest(request, "PATCH");

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "PATCH Error:" << reply->errorString();
        } else {
            QByteArray responseData = reply->readAll();
            qDebug() << "PATCH Success:" << responseData;
        }
        reply->deleteLater();
    });
}

void NetworkService::patch(const QString& endpoint, const QJsonObject& json) {
    QNetworkRequest request(QUrl("http://43.201.162.230:8000" + endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    QJsonDocument doc(json);
    QByteArray body = doc.toJson();

    qDebug() << "[PATCH]" << endpoint << body;

    QNetworkAccessManager* patchManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = patchManager->sendCustomRequest(request, "PATCH", body);

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "PATCH Error:" << reply->errorString();
        } else {
            QByteArray responseData = reply->readAll();
            qDebug() << "PATCH Success:" << responseData;
        }
        reply->deleteLater();
    });
}

void NetworkService::del(const QString& endpoint) {
    QUrl url("http://43.201.162.230:8000" + endpoint);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json; charset=utf-8");

    qDebug() << "[DELETE]" << url.toString();

    QNetworkReply* reply = manager->sendCustomRequest(request, "DELETE");

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "❌ DELETE Error:" << reply->errorString();
        } else {
            QByteArray responseData = reply->readAll();
            qDebug() << "✅ DELETE Success:" << responseData;
        }
        reply->deleteLater();
    });
}

void NetworkService::onReplyFinished(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network error:" << reply->errorString();
        callbackMap.remove(reply);
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();

    QJsonDocument doc = QJsonDocument::fromJson(responseData);

    if (doc.isArray()) {
        if (callbackMap.contains(reply)) {
            qDebug() << "[응답 콜백 실행 중...]";
            callbackMap[reply](doc.array());
        } else {
            qDebug() << "[경고] 콜백이 존재하지 않음.";
        }
    } else {
        qDebug() << "[경고] 응답 형식이 JSON 배열이 아님:" << responseData;
    }

    callbackMap.remove(reply);
    reply->deleteLater();
}
