#include "simplefacility.h"
#include "NetworkService.h"

// simplefacility.cpp
SimpleFacility::SimpleFacility(const QString& name, int minutes, int facilityId)
    : facility(name, minutes, facilityId){
    timer = new TimerWidget(minutes);
}

void SimpleFacility::startTimer() {
    timer->start();
    wsServer.broadcast(QString("{\"facility\":%1,\"action\":\"start\"}").arg(facilityId));
}

void SimpleFacility::stopTimer() {
    timer->stop();
    wsServer.broadcast(QString("{\"facility\":%1,\"action\":\"pause\"}").arg(facilityId));
}

void SimpleFacility::resetTimer() {
    timer->reset();
    wsServer.broadcast(QString("{\"facility\":%1,\"action\":\"stop\"}").arg(facilityId));
}

void SimpleFacility::setManualTime(int minutes) {
    timer->setTime(minutes);
    timer->start();
}

void SimpleFacility::setAvailable() {
    QString endpoint = QString("/facility/%1/status?status=active").arg(facilityId);
    NetworkService::instance().patch(endpoint);
}

void SimpleFacility::setUnavailable() {
    QString endpoint = QString("/facility/%1/status?status=off").arg(facilityId);
    NetworkService::instance().patch(endpoint);
}

void SimpleFacility::bindUI(QPushButton* startBtn, QPushButton* stopBtn, QPushButton* resetBtn,
                            QPushButton* availableBtn, QPushButton* unavailableBtn,
                            QLabel* timeLabel, QPushButton* manualSetBtn, QLineEdit* manualInput) {
    connect(startBtn, &QPushButton::clicked, this, &SimpleFacility::startTimer);
    connect(stopBtn, &QPushButton::clicked, this, &SimpleFacility::stopTimer);
    connect(resetBtn, &QPushButton::clicked, this, &SimpleFacility::resetTimer);
    connect(availableBtn, &QPushButton::clicked, this, [=]() { setAvailable(); });
    connect(unavailableBtn, &QPushButton::clicked, this, [=]() { setUnavailable(); });
    connect(timer, &TimerWidget::timeUpdated, timeLabel, &QLabel::setText);

    connect(manualSetBtn, &QPushButton::clicked, this, [=]() {
        bool ok = false;
        int minutes = manualInput->text().toInt(&ok);

        if (!ok || minutes <= 0 || minutes > 60) {
            // 유효하지 않은 입력이거나 60 초과일 경우 무시 (원한다면 경고창 추가 가능)
            return;
        }

        setManualTime(minutes);
    });
}
