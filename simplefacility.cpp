#include "simplefacility.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

SimpleFacility::SimpleFacility(const QString& name, int minutes, QWidget* parent)
    : facility(name, minutes) {
    container = new QWidget(parent);
    QVBoxLayout* outerLayout = new QVBoxLayout(container);

    QWidget* innerWidget = new QWidget(container); // 별도 레이아웃 적용용 위젯
    QVBoxLayout* innerLayout = new QVBoxLayout(innerWidget);

    QLabel* label = new QLabel(name, innerWidget);
    label->setAlignment(Qt::AlignCenter);

    timer = new TimerWidget(minutes, innerWidget);

    innerLayout->addWidget(label);
    innerLayout->addWidget(timer);
    innerWidget->setLayout(innerLayout);

    outerLayout->addWidget(innerWidget);
    container->setLayout(outerLayout);
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
