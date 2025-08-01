#include "reservationmanager.h"
#include "NetworkService.h"
#include <QJsonArray>

ReservationManager::ReservationManager(const QString& facilityName, QObject* parent)
    : QObject(parent), facilityName(facilityName)
{
    loadReservations();
}

void ReservationManager::loadReservations() {
    reservationList = {
        {"김민준", "이서연"},
        {"박지후", "한서우", "최다은"}
    };
}

const QVector<QStringList>& ReservationManager::getReservationList() const {
    return reservationList;
}

void ReservationManager::removeReservation(int index) {
    if (index >= 0 && index < reservationList.size()) {
        reservationList.removeAt(index);
        // TODO: 백엔드 삭제 API 호출
    }
}

void ReservationManager::editReservation(int index, const QStringList& newNames) {
    if (index >= 0 && index < reservationList.size()) {
        reservationList[index] = newNames;
        // TODO: 백엔드 수정 API 호출
    }
}

void ReservationManager::onUseClicked() {
    if (reservationList.isEmpty()) return;

    QJsonObject payload;
    payload["facility"] = facilityName;
    QJsonArray users;
    for (const auto& name : reservationList.first()) {
        users.append(name);
    }
    payload["users"] = users;

    sendToBackend("use", payload);
    reservationList.removeFirst();
}

void ReservationManager::onCloseClicked() {
    QJsonObject payload;
    payload["facility"] = facilityName;
    sendToBackend("close", payload);
}

void ReservationManager::bindButtons(QPushButton* useBtn, QPushButton* closeBtn) {
    connect(useBtn, &QPushButton::clicked, this, &ReservationManager::onUseClicked);
    connect(closeBtn, &QPushButton::clicked, this, &ReservationManager::onCloseClicked);
}

void ReservationManager::sendToBackend(const QString& action, const QJsonObject& payload) {
    NetworkService::instance().post("/facility/" + action, payload);
}
