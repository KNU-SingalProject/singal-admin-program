#ifndef SIMPLEFACILITY_H
#define SIMPLEFACILITY_H

#include "facility.h"
#include "timerwidget.h"
#include <QJsonObject>
#include <QPushButton>
#include <QLabel>
#include <qlineedit.h>

class SimpleFacility : public facility {
private:
    TimerWidget* timer;

public:
    SimpleFacility(const QString& name, int minutes);

    void startTimer() override;
    void stopTimer() override;
    void resetTimer() override;

    void setManualTime(int minutes); // 수동 타이머

    void setAvailable(int index = 0) override;
    void setUnavailable(int index = 0) override;

    void bindUI(QPushButton* startBtn, QPushButton* stopBtn, QPushButton* resetBtn,
                QPushButton* availableBtn, QPushButton* unavailableBtn, QLabel* timeLabel,
                QPushButton* manualSetBtn, QLineEdit* manualInput);
};

#endif // SIMPLEFACILITY_H
