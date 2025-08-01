#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#pragma once

#include "ComputerFacility.h"
#include "SimpleFacility.h"

class MainController {
private:
    ComputerFacility* computer;
    SimpleFacility* nintendo;
    SimpleFacility* karaoke;
    SimpleFacility* badminton;

public:
    MainController();
    ~MainController();

    // 컴퓨터
    void bindComputerUI(QVector<QPushButton*> pcAvailableBtns, QVector<QPushButton*> pcUnavailableBtns,
                        QVector<QPushButton*> pcResetBtns, QVector<QLabel*> pcTimeLabels);

    // 닌텐도
    void bindNintendoUI(QPushButton* nintendoStartBtn, QPushButton* nintendoStopBtn, QPushButton* nintendoResetBtn,
                        QPushButton* nintendoAvailableBtn, QPushButton* nintendoUnavailableBtn,
                        QLabel* nintendoTimeLabel);

    // 노래방
    void bindKaraokeUI(QPushButton* karaokeStartBtn, QPushButton* karaokeStopBtn, QPushButton* karaokeResetBtn,
                       QPushButton* karaokeAvailableBtn, QPushButton* karaokeUnavailableBtn,
                       QLabel* karaokeTimeLabel);

    // 패드민턴
    void bindBadmintonUI(QPushButton* badmintonStartBtn, QPushButton* badmintonStopBtn, QPushButton* badmintonResetBtn,
                         QPushButton* badmintonAvailableBtn, QPushButton* badmintonUnavailableBtn,
                         QLabel* badmintonTimeLabel);
};

#endif // MAINCONTROLLER_H
