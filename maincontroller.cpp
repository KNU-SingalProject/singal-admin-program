#include "MainController.h"

MainController::MainController() {
    computer = new ComputerFacility();
    nintendo = new SimpleFacility("닌텐도", 60, 2);
    karaoke = new SimpleFacility("노래방", 62, 3);
    badminton = new SimpleFacility("패드민턴", 30, 4);
}

MainController::~MainController() {
    delete computer;
    delete nintendo;
    delete karaoke;
    delete badminton;
}

// 컴퓨터
void MainController::bindComputerUI(QVector<QPushButton*> pcAvailableBtns, QVector<QPushButton*> pcUnavailableBtns,
                                    QVector<QPushButton*> pcResetBtns, QVector<QLabel*> pcTimeLabels) {
    computer->bindUI(pcAvailableBtns, pcUnavailableBtns, pcResetBtns, pcTimeLabels);
}

// 닌텐도
void MainController::bindNintendoUI(QPushButton* nintendoStartBtn, QPushButton* nintendoStopBtn, QPushButton* nintendoResetBtn,
                                    QPushButton* nintendoAvailableBtn, QPushButton* nintendoUnavailableBtn,
                                    QLabel* nintendoTimeLabel, QPushButton* manualSetBtn, QLineEdit* manualInput){
    nintendo->bindUI(nintendoStartBtn, nintendoStopBtn, nintendoResetBtn, nintendoAvailableBtn, nintendoUnavailableBtn,
                     nintendoTimeLabel, manualSetBtn, manualInput);
}

// 노래방
void MainController::bindKaraokeUI(QPushButton* karaokeStartBtn, QPushButton* karaokeStopBtn, QPushButton* karaokeResetBtn,
                                   QPushButton* karaokeAvailableBtn, QPushButton* karaokeUnavailableBtn,
                                   QLabel* karaokeTimeLabel, QPushButton* manualSetBtn, QLineEdit* manualInput) {
    karaoke->bindUI(karaokeStartBtn, karaokeStopBtn, karaokeResetBtn, karaokeAvailableBtn, karaokeUnavailableBtn,
                    karaokeTimeLabel, manualSetBtn, manualInput);
}

// 패드민턴
void MainController::bindBadmintonUI(QPushButton* badmintonStartBtn, QPushButton* badmintonStopBtn, QPushButton* badmintonResetBtn,
                                     QPushButton* badmintonAvailableBtn, QPushButton* badmintonUnavailableBtn,
                                     QLabel* badmintonTimeLabel, QPushButton* manualSetBtn, QLineEdit* manualInput) {
    badminton->bindUI(badmintonStartBtn, badmintonStopBtn, badmintonResetBtn, badmintonAvailableBtn, badmintonUnavailableBtn,
                      badmintonTimeLabel, manualSetBtn, manualInput);
}
