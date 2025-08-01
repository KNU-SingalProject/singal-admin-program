#include "MainController.h"

MainController::MainController() {
    computer = new ComputerFacility();
    nintendo = new SimpleFacility("닌텐도", 30);
    karaoke = new SimpleFacility("노래방", 30);
    badminton = new SimpleFacility("패드민턴", 30);
}

MainController::~MainController() {
    delete computer;
    delete nintendo;
    delete karaoke;
    delete badminton;
}

ComputerFacility* MainController::getComputerFacility() const {
    return computer;
}

SimpleFacility* MainController::getNintendo() const {
    return nintendo;
}

SimpleFacility* MainController::getKaraoke() const {
    return karaoke;
}

SimpleFacility* MainController::getBadminton() const {
    return badminton;
}
