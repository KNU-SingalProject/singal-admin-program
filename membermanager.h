#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <QObject>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QTableWidget>
#include <QComboBox>

class MemberManager : public QObject
{
    Q_OBJECT

public:
    explicit MemberManager(QObject* parent = nullptr);

    void bindUI(
        QLineEdit* memberIdEdit,
        QLineEdit* nameEdit,
        QComboBox* genderCombo,
        QDateEdit* birthEdit,
        QLineEdit* phoneEdit,
        QPushButton* registerBtn,
        QTableWidget* memberTable
        );

private slots:
    void onRegisterClicked();
    void fetchMembers();  // 테이블 초기화용

private:
    QLineEdit* memberIdEdit;
    QLineEdit* nameEdit;
    QComboBox* genderCombo;
    QDateEdit* birthEdit;
    QLineEdit* phoneEdit;
    QPushButton* registerBtn;
    QTableWidget* memberTable;
};

#endif // MEMBERMANAGER_H
