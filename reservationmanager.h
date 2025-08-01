#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QPushButton>
#include <QJsonObject>

class ReservationManager : public QObject
{
    Q_OBJECT

private:
    QString facilityName;
    QVector<QStringList> reservationList;

    void sendToBackend(const QString& action, const QJsonObject& payload);

private slots:
    void onUseClicked();
    void onCloseClicked();

public:
    explicit ReservationManager(const QString& facilityName, QObject* parent = nullptr);

    const QVector<QStringList>& getReservationList() const;
    void loadReservations();

    void removeReservation(int index);
    void editReservation(int index, const QStringList& newNames);

    void bindButtons(QPushButton* useBtn, QPushButton* closeBtn);
};

#endif // RESERVATIONMANAGER_H
