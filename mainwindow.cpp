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
        ui->label_nintendo_time,
        ui->btn_nintendo_manual_set,
        ui->lineedit_nintendo_manual);

    // 노래방
    controller->bindKaraokeUI(
        ui->btn_karaoke_start,
        ui->btn_karaoke_stop,
        ui->btn_karaoke_reset,
        ui->btn_karaoke_available,
        ui->btn_karaoke_unavailable,
        ui->label_karaoke_time,
        ui->btn_karaoke_manual_set,
        ui->lineedit_karaoke_manual);

    // 패드민턴
    controller->bindBadmintonUI(
        ui->btn_badminton_start,
        ui->btn_badminton_stop,
        ui->btn_badminton_reset,
        ui->btn_badminton_available,
        ui->btn_badminton_unavailable,
        ui->label_badminton_time,
        ui->btn_badminton_manual_set,
        ui->lineedit_badminton_manual);

    pcReservationManager = new ReservationManager("PC", this);
    pcReservationManager->bindButtons(
        ui->btn_pc_use,
        ui->btn_pc_finish);

    pcReservationManager->bindUI({
        ui->value_pc_slot_1,
        ui->value_pc_slot_2,
        ui->value_pc_slot_3,
        ui->value_pc_slot_4,
        ui->value_pc_slot_5,
        ui->value_pc_slot_6,
        ui->value_pc_slot_7,
        ui->value_pc_slot_8,
        ui->value_pc_slot_9,
        ui->value_pc_slot_10
    });

    nintendoReservationManager = new ReservationManager("닌텐도", this);
    nintendoReservationManager->bindButtons(
        ui->btn_nintendo_use,
        ui->btn_nintendo_finish);

    nintendoReservationManager->bindUI({
        ui->value_nintendo_slot_1,
        ui->value_nintendo_slot_2,
        ui->value_nintendo_slot_3,
        ui->value_nintendo_slot_4,
        ui->value_nintendo_slot_5,
        ui->value_nintendo_slot_6,
        ui->value_nintendo_slot_7,
        ui->value_nintendo_slot_8,
        ui->value_nintendo_slot_9,
        ui->value_nintendo_slot_10
    });

    karaokeReservationManager = new ReservationManager("노래방", this);
    karaokeReservationManager->bindButtons(
        ui->btn_karaoke_use,
        ui->btn_karaoke_finish);

    karaokeReservationManager->bindUI({
        ui->value_karaoke_slot_1,
        ui->value_karaoke_slot_2,
        ui->value_karaoke_slot_3,
        ui->value_karaoke_slot_4,
        ui->value_karaoke_slot_5,
        ui->value_karaoke_slot_6,
        ui->value_karaoke_slot_7,
        ui->value_karaoke_slot_8,
        ui->value_karaoke_slot_9,
        ui->value_karaoke_slot_10
    });

    badmintonReservationManager = new ReservationManager("패드민턴", this);
    badmintonReservationManager->bindButtons(
        ui->btn_badminton_use,
        ui->btn_badminton_finish);

    badmintonReservationManager->bindUI({
        ui->value_badminton_slot_1,
        ui->value_badminton_slot_2,
        ui->value_badminton_slot_3,
        ui->value_badminton_slot_4,
        ui->value_badminton_slot_5,
        ui->value_badminton_slot_6,
        ui->value_badminton_slot_7,
        ui->value_badminton_slot_8,
        ui->value_badminton_slot_9,
        ui->value_badminton_slot_10
    });

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
