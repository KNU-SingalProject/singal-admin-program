#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainController.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //controller = new MainController(this);

    memberManager = new MemberManager(this);
    memberManager->bindUI(
        ui->lineEdit_memberID,
        ui->lineEdit_name,
        ui->comboBox_gender,
        ui->dateEdit_birth,
        ui->lineEdit_phone,
        ui->btn_register,
        ui->table_members
        );
}

MainWindow::~MainWindow() {
    delete ui;
}
