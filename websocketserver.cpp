// WebSocketServer.cpp
#include "WebSocketServer.h"
#include <QDebug>

WebSocketServer::WebSocketServer(QObject *parent)
    : QObject(parent),
    server(new QWebSocketServer(QStringLiteral("FacilityServer"), QWebSocketServer::NonSecureMode, this))
{
    if (!server) {
        qCritical() << "[WebSocket] 서버 객체 생성 실패!";
        return;
    }

    bool ok = server->listen(QHostAddress::AnyIPv4, 8081);
    if (ok) {
        qDebug() << "[WebSocket] 서버 실행 성공, 포트: 8081";
        connect(server, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
    } else {
        qCritical() << "[WebSocket] 서버 실행 실패!";
    }
}

void WebSocketServer::onNewConnection() {
    QWebSocket *socket = server->nextPendingConnection();
    clients << socket;
    qDebug() << "[WebSocket] 클라이언트 연결됨";

    connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onSocketDisconnected);
}

void WebSocketServer::onTextMessageReceived(QString message) {
    qDebug() << "[WebSocket] 메시지 수신:" << message;
}

void WebSocketServer::onSocketDisconnected() {
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        clients.removeAll(socket);
        socket->deleteLater();
        qDebug() << "[WebSocket] 클라이언트 연결 해제";
    }
}

void WebSocketServer::broadcast(const QString &message) {
    qDebug() << "[WebSocket] 브로드캐스트:" << message;
    for (QWebSocket *client : clients) {
        if (client->isValid()) {
            client->sendTextMessage(message);
        }
    }
}
