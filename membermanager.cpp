#include "membermanager.h"
#include "NetworkService.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonObject>

MemberManager::MemberManager(QWidget* parent) : QWidget(parent) {
    memberIdEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    genderEdit = new QLineEdit(this);
    birthEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);

    QPushButton* saveBtn = new QPushButton("저장", this);
    connect(saveBtn, &QPushButton::clicked, this, &MemberManager::onSaveClicked);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("회원 번호")); layout->addWidget(memberIdEdit);
    layout->addWidget(new QLabel("이름")); layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("성별")); layout->addWidget(genderEdit);
    layout->addWidget(new QLabel("생일")); layout->addWidget(birthEdit);
    layout->addWidget(new QLabel("전화번호")); layout->addWidget(phoneEdit);
    layout->addWidget(saveBtn);
    setLayout(layout);
}

void MemberManager::onSaveClicked() {
    QJsonObject payload;
    payload["memberId"] = memberIdEdit->text();
    payload["name"] = nameEdit->text();
    payload["gender"] = genderEdit->text();
    payload["birth"] = birthEdit->text();
    payload["phone"] = phoneEdit->text();

    NetworkService::instance().post("/member/add", payload);
}

QWidget* MemberManager::getUI() {
    return this;
}
