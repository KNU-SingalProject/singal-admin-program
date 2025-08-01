#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MainController.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    controller = new MainController(this);

    // 시설 사용 탭 내 각 섹션에 배치
    ui->layout_pc1->addWidget(controller->getComputerTimer(0));
    ui->layout_pc2->addWidget(controller->getComputerTimer(1));
    ui->layout_pc3->addWidget(controller->getComputerTimer(2));
    ui->layout_pc4->addWidget(controller->getComputerTimer(3));

    ui->layout_nintendo_timer->addWidget(controller->getNintendoUI());
    ui->layout_karaoke_timer->addWidget(controller->getKaraokeUI());
    ui->layout_badminton_timer->addWidget(controller->getBadmintonUI());

    ui->layout_reservation_pc->addWidget(controller->getReservationUI("컴퓨터"));
    ui->layout_reservation_nintendo->addWidget(controller->getReservationUI("닌텐도"));
    ui->layout_reservation_karaoke->addWidget(controller->getReservationUI("노래방"));
    ui->layout_reservation_badminton->addWidget(controller->getReservationUI("패드민턴"));

    // 회원가입 탭
    ui->layout_member->addWidget(controller->getMemberUI());
}

MainWindow::~MainWindow() {
    delete ui;
}
