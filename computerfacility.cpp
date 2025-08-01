#include "computerfacility.h"
#include "NetworkService.h"

// computerfacility.cpp
ComputerFacility::ComputerFacility()
    : facility("컴퓨터", 60) {
    for (int i = 0; i < 4; ++i) {
        TimerWidget* timer = new TimerWidget(usageMinutes);
        computerTimers.append(timer);
    }
}

void ComputerFacility::startTimer(int index) {
    if (index >= 0 && index < computerTimers.size()) {
        computerTimers[index]->start();
    }
}

void ComputerFacility::stopTimer(int index) {
    if (index >= 0 && index < computerTimers.size()) {
        computerTimers[index]->stop();
    }
}

void ComputerFacility::resetTimer(int index) {
    if (index >= 0 && index < computerTimers.size()) {
        computerTimers[index]->reset();
    }
}

void ComputerFacility::resetTimer() {
    for (auto timer : computerTimers) {
        timer->reset();
    }
}

void ComputerFacility::setAvailable(int index) {
    QJsonObject payload;
    payload["pc_number"] = index + 1;
    payload["status"] = "available";
    NetworkService::instance().post("/facilities/update-status", payload);
}

void ComputerFacility::setUnavailable(int index) {
    QJsonObject payload;
    payload["pc_number"] = index + 1;
    payload["status"] = "unavailable";
    NetworkService::instance().post("/facilities/update-status", payload);
}

void ComputerFacility::bindUI(QVector<QPushButton*> availableBtns, QVector<QPushButton*> unavailableBtns, QVector<QPushButton*> resetBtns, QVector<QLabel*> timeLabels) {
    for (int i = 0; i < availableBtns.size(); ++i) {
        connect(availableBtns[i], &QPushButton::clicked, [=]() {
            setAvailable(i);
        });
    }

    for (int i = 0; i < unavailableBtns.size(); ++i) {
        connect(unavailableBtns[i], &QPushButton::clicked, [=]() {
            setUnavailable(i);
        });
    }

    for (int i = 0; i < resetBtns.size(); ++i) {
        connect(resetBtns[i], &QPushButton::clicked, [=]() {
            resetTimer(i);
        });
    }

    for (int i = 0; i < timeLabels.size(); ++i) {
        connect(computerTimers[i], &TimerWidget::timeUpdated, timeLabels[i], &QLabel::setText);
    }

}
