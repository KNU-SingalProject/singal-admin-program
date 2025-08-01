#include "reservationmanager.h"
#include "NetworkService.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QJsonArray>

ReservationManager::ReservationManager(const QString& facilityName, QWidget* parent)
    : QObject(parent), facilityName(facilityName) {
    container = new QWidget(parent);
    reservationWidget = new QListWidget(container);

    QPushButton* useBtn = new QPushButton("시설 이용");
    QPushButton* closeBtn = new QPushButton("시설 마감");

    connect(useBtn, &QPushButton::clicked, this, &ReservationManager::onUseClicked);
    connect(closeBtn, &QPushButton::clicked, this, &ReservationManager::onCloseClicked);

    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->addWidget(new QLabel(facilityName + " 예약자 목록"));
    layout->addWidget(reservationWidget);
    layout->addWidget(useBtn);
    layout->addWidget(closeBtn);
    container->setLayout(layout);

    loadReservations();
}

void ReservationManager::loadReservations() {
    // 예시: 더미 데이터
    reservationList = {
        {"김민준", "이서연"},
        {"박지후", "한서우", "최다은"}
    };
    refreshUI();
}

void ReservationManager::refreshUI() {
    reservationWidget->clear();
    for (int i = 0; i < reservationList.size(); ++i) {
        QStringList names = reservationList[i];
        QString teamInfo = QString("팀 %1: ").arg(i + 1) + names.join(", ");
        QListWidgetItem* item = new QListWidgetItem(teamInfo);
        reservationWidget->addItem(item);
    }
}

void ReservationManager::onDeleteClicked() {
    int row = reservationWidget->currentRow();
    if (row >= 0) {
        reservationList.remove(row);
        refreshUI();
        // TODO: 백엔드 삭제 API 호출
    }
}

void ReservationManager::onEditClicked() {
    int row = reservationWidget->currentRow();
    if (row >= 0) {
        QString newNames = QInputDialog::getText(container, "수정", "새 이름 입력 (쉼표로 구분)");
        reservationList[row] = newNames.split(",", Qt::SkipEmptyParts);
        refreshUI();
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
    refreshUI();
}

void ReservationManager::onCloseClicked() {
    QJsonObject payload;
    payload["facility"] = facilityName;
    sendToBackend("close", payload);
}

void ReservationManager::sendToBackend(const QString& action, const QJsonObject& payload) {
    NetworkService::instance().post("/facility/" + action, payload);
}

QWidget* ReservationManager::getUI() {
    return container;
}
