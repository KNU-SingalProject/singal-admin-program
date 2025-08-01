#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#pragma once

#include "ComputerFacility.h"
#include "SimpleFacility.h"
#include "ReservationManager.h"
#include "MemberManager.h"

class MainController {
private:
    ComputerFacility* computer;
    SimpleFacility* nintendo;
    SimpleFacility* karaoke;
    SimpleFacility* badminton;

    ReservationManager* reservationComputer;
    ReservationManager* reservationNintendo;
    ReservationManager* reservationKaraoke;
    ReservationManager* reservationBadminton;

    MemberManager* memberManager;
public:
    MainController(QWidget* parent) {
        computer = new ComputerFacility(parent);
        nintendo = new SimpleFacility("닌텐도", 60, parent);
        karaoke = new SimpleFacility("노래방", 62, parent);
        badminton = new SimpleFacility("패드민턴", 30, parent);

        reservationComputer = new ReservationManager("컴퓨터", parent);
        reservationNintendo = new ReservationManager("닌텐도", parent);
        reservationKaraoke = new ReservationManager("노래방", parent);
        reservationBadminton = new ReservationManager("패드민턴", parent);

        memberManager = new MemberManager(parent);
    }

    // ✅ 각 PC 타이머 UI 반환 (0~3)
    QWidget* getComputerTimer(int index) const {
        return computer->getTimerUI(index);
    }

    // 개별 시설 UI
    QWidget* getNintendoUI() const { return nintendo->getUI(); }
    QWidget* getKaraokeUI() const { return karaoke->getUI(); }
    QWidget* getBadmintonUI() const { return badminton->getUI(); }

    // 예약자 리스트 UI
    QWidget* getReservationUI(const QString& facility) const {
        if (facility == "컴퓨터") return reservationComputer->getUI();
        if (facility == "닌텐도") return reservationNintendo->getUI();
        if (facility == "노래방") return reservationKaraoke->getUI();
        if (facility == "패드민턴") return reservationBadminton->getUI();
        return nullptr;
    }
};

#endif // MAINCONTROLLER_H
