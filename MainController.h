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

    ComputerFacility* getComputerFacility() const;
    SimpleFacility* getNintendo() const;
    SimpleFacility* getKaraoke() const;
    SimpleFacility* getBadminton() const;
};

#endif // MAINCONTROLLER_H
