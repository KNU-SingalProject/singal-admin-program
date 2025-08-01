#include "timerwidget.h"

TimerWidget::TimerWidget(int defaultMinutes, QWidget* parent)
    : QWidget(parent), defaultMinutes(defaultMinutes)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimerWidget::updateTimer);

    remainingTime = QTime(0, defaultMinutes, 0);
    emit timeUpdated(remainingTime.toString("mm:ss"));  // 초기값 emit
}

void TimerWidget::start() {
    if (!timer->isActive())
        timer->start(1000);
}

void TimerWidget::stop() {
    timer->stop();
}

void TimerWidget::reset() {
    stop();
    remainingTime = QTime(0, defaultMinutes, 0);
    emit timeUpdated(remainingTime.toString("mm:ss"));
}

void TimerWidget::setTime(int minutes) {
    stop();
    remainingTime = QTime(0, minutes, 0);
    emit timeUpdated(remainingTime.toString("mm:ss"));
}

void TimerWidget::updateTimer() {
    if (remainingTime == QTime(0, 0, 0)) {
        timer->stop();
        emit timeout();
        return;
    }

    remainingTime = remainingTime.addSecs(-1);
    emit timeUpdated(remainingTime.toString("mm:ss"));
}

QTime TimerWidget::getRemainingTime() const {
    return remainingTime;
}
