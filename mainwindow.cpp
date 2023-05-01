#include "mainwindow.h"
#include "adminlogin.h"
#include "ui_mainwindow.h"
#include "informationview.h"
#include "tourpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      sm {new StadiumManager()}
{
    ui->setupUi(this);

    sm->readDB();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_adminButton_clicked()
{
    AdminLogin adminWindow;
    adminWindow.setModal(true);
    adminWindow.exec();
}


void MainWindow::on_viewInfoButton_clicked()
{
    InformationView infoPage;
    infoPage.setModal(true);
    infoPage.exec();
}


void MainWindow::on_beginButton_clicked()
{
//    qDebug() << "Souvenirs\n";
//    for(auto& souvenir : sm->getStadium("Marlins Park")->getSouvenirs())
//    {
//        qDebug() << souvenir.name << ": " << souvenir.price;
//    }

    TourPage tourPage(this, sm);
    tourPage.setModal(true);
    tourPage.exec();
}

