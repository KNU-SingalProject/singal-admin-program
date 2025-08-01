#include "computerfacility.h"

ComputerFacility::ComputerFacility(QWidget* parent) : facility("컴퓨터", 60) {
    container = new QWidget(parent);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (int i = 0; i < 4; ++i) {
        TimerWidget* timer = new TimerWidget(usageMinutes);
        computerTimers.append(timer);
        layout->addWidget(timer);
    }

    container->setLayout(layout);
}

void ComputerFacility::startTimer() {
    for (auto timer : computerTimers) {
        timer->start();
    }
}

void ComputerFacility::stopTimer() {
    for (auto timer : computerTimers) {
        timer->stop();
    }
}

void ComputerFacility::resetTimer() {
    for (auto timer : computerTimers) {
        timer->reset();
    }
}

QWidget* ComputerFacility::getUI() {
    return container;
}
