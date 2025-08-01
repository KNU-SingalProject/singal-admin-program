#include "simplefacility.h"

#include <QVBoxLayout>
#include <QLabel>

SimpleFacility::SimpleFacility(const QString& name, int minutes, QWidget* parent)
    : facility(name, minutes) {
    timer = new TimerWidget(minutes);
    container = new QWidget(parent);

    QVBoxLayout* layout = new QVBoxLayout(container);
    QLabel* label = new QLabel(name, container);
    layout->addWidget(label);
    layout->addWidget(timer);
    container->setLayout(layout);
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

QWidget* SimpleFacility::getUI() {
    return container;
}
