#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QJsonObject>

class ReservationManager : public QObject
{
    Q_OBJECT

private slots:
    void onDeleteClicked();
    void onEditClicked();
    void onUseClicked();
    void onCloseClicked();

private:
    QString facilityName;
    QVector<QStringList> reservationList;
    QListWidget* reservationWidget;
    QWidget* container;

    void refreshUI();
    void sendToBackend(const QString& action, const QJsonObject& payload);

public:
    explicit ReservationManager(const QString& facilityName, QWidget* parent = nullptr);

    QWidget* getUI();
    void loadReservations(); // API 호출로 로딩
    void removeReservation(int index);
    void editReservation(int index, const QStringList& newNames);
    void useFacility();  // 시설 이용
    void closeFacility(); // 마감 처리
};

#endif // RESERVATIONMANAGER_H
