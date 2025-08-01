#include "mainwindow.h"

#include <QApplication>

// main.cpp
#include "websocketserver.h"

WebSocketServer wsServer;  // ✅ 실제 객체 정의

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
