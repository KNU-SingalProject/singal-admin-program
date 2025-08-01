#include "timerwidget.h"
#include <QVBoxLayout>

TimerWidget::TimerWidget(int defaultMinutes, QWidget* parent) : QWidget(parent), defaultMinutes(defaultMinutes) {
    timeDisplay = new QLabel("00:00", this);
    startBtn = new QPushButton("시작", this);
    stopBtn = new QPushButton("정지", this);
    resetBtn = new QPushButton("초기화", this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TimerWidget::updateTimer);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(timeDisplay);
    layout->addWidget(startBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(resetBtn);
    setLayout(layout);

    connect(startBtn, &QPushButton::clicked, this, &TimerWidget::start);
    connect(stopBtn, &QPushButton::clicked, this, &TimerWidget::stop);
    connect(resetBtn, &QPushButton::clicked, this, &TimerWidget::reset);

    reset();
}

void TimerWidget::start() {
    timer->start(1000); // 매초마다
}

void TimerWidget::stop() {
    timer->stop();
}

void TimerWidget::reset() {
    remainingTime = QTime(0, defaultMinutes, 0);
    timeDisplay->setText(remainingTime.toString("mm:ss"));
}

void TimerWidget::setTime(int minutes) {
    remainingTime = QTime(0, minutes, 0);
    timeDisplay ->setText(remainingTime.toString("mm:ss"));
}

void TimerWidget::updateTimer() {
    if (remainingTime == QTime(0, 0, 0)) {
        timer->stop();
        emit timeout();
        return;
    }
    remainingTime = remainingTime.addSecs(-1);
    timeDisplay->setText(remainingTime.toString("mm:ss"));
}

QTime TimerWidget::getRemainingTime() const {
    return remainingTime;
}
