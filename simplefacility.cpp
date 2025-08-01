#include "simplefacility.h"
#include "NetworkService.h"

// simplefacility.cpp
SimpleFacility::SimpleFacility(const QString& name, int minutes)
    : facility(name, minutes) {
    timer = new TimerWidget(minutes);
}

void SimpleFacility::startTimer() {
    timer->start();
}

void SimpleFacility::stopTimer() {
    timer->stop();
}

void SimpleFacility::resetTimer() {
    timer->reset();
}

void SimpleFacility::setManualTime(int minutes) {
    timer->setTime(minutes);
}

void SimpleFacility::setAvailable(int) {
    QJsonObject payload;
    payload["facility_name"] = name;
    payload["status"] = "available";
    NetworkService::instance().post("/facilities/update-status", payload);
}

void SimpleFacility::setUnavailable(int) {
    QJsonObject payload;
    payload["facility_name"] = name;
    payload["status"] = "unavailable";
    NetworkService::instance().post("/facilities/update-status", payload);
}

void SimpleFacility::bindUI(QPushButton* startBtn, QPushButton* stopBtn, QPushButton* resetBtn,
                            QPushButton* availableBtn, QPushButton* unavailableBtn, QLabel* timeLabel) {
    connect(startBtn, &QPushButton::clicked, this, &SimpleFacility::startTimer);
    connect(stopBtn, &QPushButton::clicked, this, &SimpleFacility::stopTimer);
    connect(resetBtn, &QPushButton::clicked, this, &SimpleFacility::resetTimer);
    connect(availableBtn, &QPushButton::clicked, this, [=]() { setAvailable(); });
    connect(unavailableBtn, &QPushButton::clicked, this, [=]() { setUnavailable(); });
    connect(timer, &TimerWidget::timeUpdated, timeLabel, &QLabel::setText);
}
