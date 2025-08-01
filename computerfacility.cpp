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
