#ifndef MEMBERMANAGER_H
#define MEMBERMANAGER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class MemberManager: public QWidget
{
    Q_OBJECT

private slots:
    void onSaveClicked();

private:
    QLineEdit* memberIdEdit;
    QLineEdit* nameEdit;
    QLineEdit* genderEdit;
    QLineEdit* birthEdit;
    QLineEdit* phoneEdit;

public:
    explicit MemberManager(QWidget* parent = nullptr);

    QWidget* getUI();
};

#endif // MEMBERMANAGER_H
