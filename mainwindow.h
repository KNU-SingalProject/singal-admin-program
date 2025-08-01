#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MainController.h"
#include "membermanager.h"
#include "reservationmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    MainController* controller;
    MemberManager* memberManager;
    ReservationManager* pcReservationManager;
    ReservationManager* nintendoReservationManager;
    ReservationManager* karaokeReservationManager;
    ReservationManager* badmintonReservationManager;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
