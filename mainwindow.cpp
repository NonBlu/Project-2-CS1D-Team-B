#include "mainwindow.h"
#include "adminlogin.h"
#include "ui_mainwindow.h"
#include "informationview.h"
#include "tourpage.h"
#include "selectyourtour.h"
#include "dynamictable.h"
#include "QApplication"
//#include "ui_tourpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui ( new Ui::MainWindow ),
      sm { new StadiumManager }, adminPage { new AdminPage(sm) }
{
    ui->setupUi(this);
    QPixmap bkgnd(":/Icons/HomeScreen2.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    adminPage->setModal(true);

    setStyleSheet("QLineEdit#nameEdit { background-color: yellow }");

    //---------------------------------------------------------
}

vector<QString> MainWindow::obtainDefaultList()
{
    vector<QString> stadiumList;

    for (auto& mlb : sm->map)
    {
        stadiumList.push_back(mlb.getStadiumName());
    }

    return stadiumList;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_adminButton_clicked()
{
    AdminLogin adminLogin(adminPage);

    adminLogin.setModal(true);

    adminLogin.exec();
}


void MainWindow::on_viewInfoButton_clicked()
{
    InformationView infoPage(sm);
    infoPage.setModal(true);
    infoPage.exec();
}


//void MainWindow::on_beginButton_clicked()
//{
//    TourPage tourPage;
//    tourPage.setModal(true);
//    tourPage.exec();
//}


void MainWindow::on_choiceButton_clicked()
{
    SelectYourTour selectTour(sm, false);
    selectTour.setModal(true);
    selectTour.exec();
}




void MainWindow::on_mstButton_clicked()
{
    vector<QString> list = obtainDefaultList();
    TourPage tourPage("Minimum Spanning Tree", list, sm);
    tourPage.setModal(true);
    tourPage.exec();
}


void MainWindow::on_dfsButton_clicked()
{
    vector<QString> list = obtainDefaultList();
    TourPage tourPage("Depth First Search", list, sm);
    tourPage.setModal(true);
    tourPage.exec();
}


void MainWindow::on_bfsButton_clicked()
{
    vector<QString> list = obtainDefaultList();
    TourPage tourPage("Breadth First Search", list, sm);
    tourPage.setModal(true);
    tourPage.exec();
}


void MainWindow::on_dynamicTableButton_clicked()
{
    DynamicTable dynTable(sm);
    dynTable.setModal(true);
    dynTable.exec();
}


void MainWindow::on_visitAllButton_clicked()
{
    SelectYourTour selectTour(sm, true);
    selectTour.setModal(true);
    selectTour.exec();
}
