#ifndef SIMPLEFACILITY_H
#define SIMPLEFACILITY_H

#include "facility.h"
#include "timerwidget.h"
#include "websocketserver.h"
#include <QJsonObject>
#include <QPushButton>
#include <QLabel>
#include <qlineedit.h>

extern WebSocketServer wsServer;

class SimpleFacility : public facility {
private:
    TimerWidget* timer;
    void writeCommandToFile(const QString& action);  // 💡 명령 저장 함수

public:
    SimpleFacility(const QString& name, int minutes, int facilityId);

    void startTimer() override;
    void stopTimer() override;
    void resetTimer() override;

    void setManualTime(int minutes); // 수동 타이머

    void setAvailable() override;
    void setUnavailable() override;

    void bindUI(QPushButton* startBtn, QPushButton* stopBtn, QPushButton* resetBtn,
                QPushButton* availableBtn, QPushButton* unavailableBtn, QLabel* timeLabel,
                QPushButton* manualSetBtn, QLineEdit* manualInput);
};

#endif // SIMPLEFACILITY_H
