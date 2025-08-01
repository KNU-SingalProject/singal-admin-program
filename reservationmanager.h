#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QJsonObject>
#include <qlabel.h>

struct ReservationEntry {
    int reservationId;
    QStringList users;
};


class ReservationManager : public QObject
{
    Q_OBJECT

private:
    QString facilityName;
    QVector<ReservationEntry> reservationList;
    QVector<QLabel*> slotLabels;

private slots:
    void onUseClicked();
    void onCloseClicked();

public:
    explicit ReservationManager(const QString& facilityName, QObject* parent = nullptr);

    int getFacilityId() const;
    const QVector<ReservationEntry>& getReservationList() const;
    void loadReservations();
    void displayReservations();

    void removeReservation(int index);
    void editReservation(int index, const QStringList& newNames);

    void bindUI(const QVector<QLabel*>& labels);
    void bindButtons(QPushButton* useBtn, QPushButton* closeBtn);
};

#endif // RESERVATIONMANAGER_H
