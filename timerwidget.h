#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTime>

class TimerWidget : public QWidget
{
    Q_OBJECT

private slots:
    void updateTimer();

private:
    int defaultMinutes;
    QTimer* timer;
    QTime remainingTime;
    QLabel* timeDisplay;
    QPushButton* startBtn;
    QPushButton* stopBtn;
    QPushButton* resetBtn;

public:
    explicit TimerWidget(int defaultMinutes, QWidget* parent = nullptr);
    void start();
    void stop();
    void reset();
    void setTime(int minutes);

    QTime getRemainingTime() const;

signals:
    void timeout();
};

#endif // TIMERWIDGET_H
