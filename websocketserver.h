// WebSocketServer.h
#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>

class WebSocketServer : public QObject {
    Q_OBJECT

public:
    explicit WebSocketServer(QObject *parent = nullptr);
    void broadcast(const QString& message);

private:
    QWebSocketServer *server;
    QList<QWebSocket*> clients;

private slots:
    void onNewConnection();
    void onTextMessageReceived(QString message);
    void onSocketDisconnected();
};

#endif // WEBSOCKETSERVER_H
