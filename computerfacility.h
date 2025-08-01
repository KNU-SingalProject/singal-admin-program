#ifndef COMPUTERFACILITY_H
#define COMPUTERFACILITY_H

#include "facility.h"
#include "timerwidget.h"
#include <QVector>
#include <QWidget>
#include <QVBoxLayout>
#include <QJsonObject>

class ComputerFacility : public facility {
private:
    QVector<TimerWidget*> computerTimers;

public:
    ComputerFacility();

    void startTimer(int index);     // 개별 PC용
    void stopTimer(int index);      // 개별 PC용
    void resetTimer(int index);     // 개별 PC용

    void startTimer() override {}   // 전체 타이머 작동 없음
    void stopTimer() override {}
    void resetTimer() override;

    virtual void setAvailable(int index = 0) override;
    virtual void setUnavailable(int index = 0) override;
};

#endif // COMPUTERFACILITY_H
