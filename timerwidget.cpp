#include "timerwidget.h"

TimerWidget::TimerWidget(int defaultMinutes, QWidget* parent)
    : QWidget(parent), defaultMinutes(defaultMinutes)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimerWidget::updateTimer);

    setTimeInternal(defaultMinutes); // 초기값 설정
    emit timeUpdated(formatTime(remainingTime));
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
    setTimeInternal(defaultMinutes);
    emit timeUpdated(formatTime(remainingTime));
}

void TimerWidget::setTime(int minutes) {
    stop();
    setTimeInternal(minutes);
    emit timeUpdated(formatTime(remainingTime));
}

void TimerWidget::updateTimer() {
    if (remainingTime == QTime(0, 0, 0)) {
        timer->stop();
        emit timeout();
        return;
    }

    remainingTime = remainingTime.addSecs(-1);
    emit timeUpdated(formatTime(remainingTime));
}

QTime TimerWidget::getRemainingTime() const {
    return remainingTime;
}

void TimerWidget::setTimeInternal(int totalMinutes) {
    if (totalMinutes <= 0) {
        remainingTime = QTime(0, 1, 0);
    } else {
        int hours = totalMinutes / 60;
        int minutes = totalMinutes % 60;
        remainingTime = QTime(hours, minutes, 0);
    }
}

QString TimerWidget::formatTime(const QTime& time) {
    if (time.hour() > 0)
        return time.toString("hh:mm:ss");
    return time.toString("mm:ss");
}
