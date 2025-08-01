#include "reservationmanager.h"
#include "NetworkService.h"
#include <QJsonArray>

ReservationManager::ReservationManager(const QString& facilityName, QObject* parent)
    : QObject(parent), facilityName(facilityName)
{
    loadReservations();
}

int ReservationManager::getFacilityId() const {
    if (facilityName == "닌텐도") return 2;
    if (facilityName == "노래방") return 3;
    if (facilityName == "패드민턴") return 4;

    return 1; // 컴퓨터
}

void ReservationManager::loadReservations() {
    int facilityId = getFacilityId();
    QString endpoint = QString("/facility/%1").arg(facilityId);

    NetworkService::instance().get(endpoint, [=](const QJsonArray& data) {
        reservationList.clear();

        for (const QJsonValue& item : data) {
            if (!item.isObject()) continue;

            QJsonObject obj = item.toObject();
            ReservationEntry entry;
            entry.reservationId = obj["reservation_id"].toInt();

            if (obj.contains("users") && obj["users"].isArray()) {
                for (const QJsonValue& user : obj["users"].toArray()) {
                    entry.users.append(user.toString());
                }
            }

            if (!entry.users.isEmpty()) {
                reservationList.append(entry);
            }
        }

        displayReservations();
    });
}

void ReservationManager::displayReservations() {
    for (QLabel* label : slotLabels) {
        label->setText("");
    }

    for (int i = 0; i < reservationList.size() && i < slotLabels.size(); ++i) {
        slotLabels[i]->setText(reservationList[i].users.join(", "));
    }
}

const QVector<ReservationEntry>& ReservationManager::getReservationList() const {
    return reservationList;
}

void ReservationManager::removeReservation(int index) {
    if (index >= 0 && index < reservationList.size()) {
        int reservationId = reservationList[index].reservationId;
        reservationList.removeAt(index);

        QString endpoint = QString("/facility?reservation=%1").arg(reservationId);
        NetworkService::instance().del(endpoint);  // 이제 진짜 맞는 URL

        displayReservations();  // UI 갱신
    }
}

void ReservationManager::editReservation(int index, const QStringList& newNames) {

}

void ReservationManager::onUseClicked() {
    if (reservationList.isEmpty()) return;

    const ReservationEntry& firstEntry = reservationList.first();

    QJsonObject payload;
    payload["facility"] = facilityName;

    QJsonArray users;
    for (const QString& name : firstEntry.users) {
        users.append(name);
    }
    payload["users"] = users;

    // TODO: 서버에 사용 기록을 보내려면 여기에 post 요청 추가
    // 예시: NetworkService::instance().post("/use", payload);

    reservationList.removeFirst();
    displayReservations(); // UI 갱신 필요
}

void ReservationManager::onCloseClicked() {
    int facilityId = getFacilityId();

    QString endpoint = QString("/facility/%1/status?status=off").arg(facilityId);
    NetworkService::instance().patch(endpoint);
}

void ReservationManager::bindUI(const QVector<QLabel*>& labels) {
    slotLabels = labels;
}

void ReservationManager::bindButtons(QPushButton* useBtn, QPushButton* closeBtn) {
    connect(useBtn, &QPushButton::clicked, this, &ReservationManager::onUseClicked);
    connect(closeBtn, &QPushButton::clicked, this, &ReservationManager::onCloseClicked);
}
