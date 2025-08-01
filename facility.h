#ifndef FACILITY_H
#define FACILITY_H

#include <QString>
#include <QWidget>

class facility
{
public:
    facility(const QString& name, int usageMinutes);
    virtual ~facility() = default;

    QString getName() const;
    int getUsageMinutes() const;

    virtual void startTimer() = 0;
    virtual void stopTimer() = 0;
    virtual void resetTimer() = 0;
    virtual QWidget* getUI() = 0;

protected:
    QString name;
    int usageMinutes;
};

#endif // FACILITY_H
