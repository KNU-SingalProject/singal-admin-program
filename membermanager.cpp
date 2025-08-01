#include "membermanager.h"
#include "NetworkService.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDate>

MemberManager::MemberManager(QObject* parent) : QObject(parent) {
}

void MemberManager::bindUI(QLineEdit* memberIdEdit,
                           QLineEdit* nameEdit,
                           QComboBox* genderCombo,
                           QDateEdit* birthEdit,
                           QLineEdit* phoneEdit,
                           QPushButton* registerBtn,
                           QTableWidget* memberTable)
{
    this->memberIdEdit = memberIdEdit;
    this->nameEdit = nameEdit;
    this->genderCombo = genderCombo;
    this->birthEdit = birthEdit;
    this->phoneEdit = phoneEdit;
    this->registerBtn = registerBtn;
    this->memberTable = memberTable;

    connect(registerBtn, &QPushButton::clicked, this, &MemberManager::onRegisterClicked);
    //fetchMembers();  // 초기 조회
}

void MemberManager::onRegisterClicked()
{
    QJsonObject payload;
    payload["memberID"] = memberIdEdit->text();  // 6자리 숫자 입력
    payload["name"] = nameEdit->text();
    payload["gender"] = genderCombo->currentText();
    payload["birth"] = birthEdit->date().toString("yyyy-MM-dd");
    payload["phone_num"] = phoneEdit->text();

    NetworkService::instance().post("/users/sign-up", payload);
    fetchMembers();
}

void MemberManager::fetchMembers()
{
    NetworkService::instance().get("/member/list", [this](const QJsonArray& arr) {
        memberTable->clearContents();
        memberTable->setRowCount(arr.size());
        memberTable->setColumnCount(4);
        memberTable->setHorizontalHeaderLabels({"이름", "전화번호", "생년월일", "주소"});

        for (int i = 0; i < arr.size(); ++i) {
            QJsonObject obj = arr[i].toObject();
            memberTable->setItem(i, 0, new QTableWidgetItem(obj["name"].toString()));
            memberTable->setItem(i, 1, new QTableWidgetItem(obj["phone"].toString()));
            memberTable->setItem(i, 2, new QTableWidgetItem(obj["birth"].toString()));
            memberTable->setItem(i, 3, new QTableWidgetItem(obj["address"].toString()));
        }
    });
}
