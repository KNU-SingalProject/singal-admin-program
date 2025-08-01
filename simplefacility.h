#ifndef SIMPLEFACILITY_H
#define SIMPLEFACILITY_H

#include "facility.h"
#include "timerwidget.h"

class SimpleFacility : public facility
{
private:
    TimerWidget* timer;
    QWidget* container;

public:
    SimpleFacility(const QString& name, int minutes, QWidget* parent = nullptr);

    void startTimer() override;
    void stopTimer() override;
    void resetTimer() override;

    QWidget* getUI() override;
    void setManualTime(int minutes); // 수동 타이머용
};

#endif // SIMPLEFACILITY_H
