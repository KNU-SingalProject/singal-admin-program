#ifndef FACILITY_H
#define FACILITY_H

#include <QString>
#include <QObject>

// facility.h
class facility : public QObject {
    Q_OBJECT

protected:
    QString name;
    int usageMinutes;
    int facilityId;

public:
    facility(const QString& name, int usageMinutes, int facilityId);
    virtual ~facility() = default;

    QString getName() const;
    int getUsageMinutes() const;

    virtual void startTimer() = 0;
    virtual void stopTimer() = 0;
    virtual void resetTimer() = 0;

    virtual void setAvailable() = 0;
    virtual void setUnavailable() = 0;
};


#endif // FACILITY_H
