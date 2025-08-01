#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 시설 이용 탭
    controller = new MainController();

    controller->bindComputerUI(
        // PC
        { ui->btn_pc1_available, ui->btn_pc2_available, ui->btn_pc3_available, ui->btn_pc4_available},
        { ui->btn_pc1_unavailable, ui->btn_pc2_unavailable, ui->btn_pc3_unavailable, ui->btn_pc4_unavailable},
        { ui->btn_pc1_reset, ui->btn_pc2_reset, ui->btn_pc3_reset, ui->btn_pc4_reset },
        { ui->label_pc1_time, ui->label_pc2_time, ui->label_pc3_time, ui->label_pc4_time});

    // 닌텐도
    controller->bindNintendoUI(
        ui->btn_nintendo_start,
        ui->btn_nintendo_stop,
        ui->btn_nintendo_reset,
        ui->btn_nintendo_available,
        ui->btn_nintendo_unavailable,
        ui->label_nintendo_time);

    // 노래방
    controller->bindKaraokeUI(
        ui->btn_karaoke_start,
        ui->btn_karaoke_stop,
        ui->btn_karaoke_reset,
        ui->btn_karaoke_available,
        ui->btn_karaoke_unavailable,
        ui->label_karaoke_time);

    // 패드민턴
    controller->bindBadmintonUI(
        ui->btn_badminton_start,
        ui->btn_badminton_stop,
        ui->btn_badminton_reset,
        ui->btn_badminton_available,
        ui->btn_badminton_unavailable,
        ui->label_badminton_time);

    // 회원 가입 탭
    memberManager = new MemberManager(this);
    memberManager->bindUI(
        ui->lineEdit_memberID,
        ui->lineEdit_name,
        ui->comboBox_gender,
        ui->dateEdit_birth,
        ui->lineEdit_phone,
        ui->btn_register,
        ui->table_members);
}

MainWindow::~MainWindow() {
    delete ui;
}
