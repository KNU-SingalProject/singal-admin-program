#ifndef COMPUTERFACILITY_H
#define COMPUTERFACILITY_H

#include "facility.h"
#include "timerwidget.h"
#include <QVector>
#include <QWidget>
#include <QVBoxLayout>

class ComputerFacility : public facility
{
private:
    QVector<TimerWidget*> computerTimers;
    QWidget* container;

public:
    ComputerFacility(QWidget* parent = nullptr);

    void startTimer() override;
    void stopTimer() override;
    void resetTimer() override;

    QWidget* getUI() override;
    QWidget* getTimerUI(int index) const;
};

#endif // COMPUTERFACILITY_H
