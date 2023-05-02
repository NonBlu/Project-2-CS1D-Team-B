#include "informationview.h"
#include "ui_informationview.h"
#include <QApplication>
#include <QTableWidget>

InformationView::InformationView(StadiumManager* sm, QWidget *parent) :
    QDialog(parent), ui(new Ui::InformationView), sm { sm }
{
    ui->setupUi(this);

    QStringList headers;
    ui->stadiumInfoTable->setColumnCount(2);
    ui->stadiumInfoTable->setHorizontalHeaderLabels(headers);
    ui->stadiumInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for(auto& mlb : sm->map) {
        QString teamName = mlb.getTeamName();
        ui->teamDropDown->addItem(teamName);
    }
}

InformationView::~InformationView()
{
    delete ui;
}

void InformationView::createTable() {
    QTableWidgetItem* tempTable;

    QString tempTeam = ui->teamDropDown->currentText();
    MLB *stadium = sm->getTeam(tempTeam);

    for(unsigned int i = 0; i < infoType.size(); i++) {
        tempTable = new QTableWidgetItem;
        ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());

        tempTable->setText(infoType[i]);
        ui->stadiumInfoTable->setItem(i, 0, tempTable);
        ui->stadiumInfoTable->resizeRowsToContents();
    }

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getStadiumName());
    ui->stadiumInfoTable->setItem(0, 1, tempTable);

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(QString::number(stadium->getSeatingCapacity()));
    ui->stadiumInfoTable->setItem(1, 1, tempTable);

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getLocation());
    ui->stadiumInfoTable->setItem(2, 1, tempTable);

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getSurface());
    ui->stadiumInfoTable->setItem(3, 1, tempTable);

    tempTable = new QTableWidgetItem;
    //ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getLeague());
    ui->stadiumInfoTable->setItem(4, 1, tempTable);

    tempTable = new QTableWidgetItem;
    //ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(QString::number(stadium->getDateOpened()));
    ui->stadiumInfoTable->setItem(5, 1, tempTable);

    tempTable = new QTableWidgetItem;
    //ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(QString::number(stadium->getFeetToCenter()));
    ui->stadiumInfoTable->setItem(6, 1, tempTable);

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(QString::number(stadium->getMetersToCenter()));
    ui->stadiumInfoTable->setItem(7, 1, tempTable);

    tempTable = new QTableWidgetItem;
   // ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getTypology());
    ui->stadiumInfoTable->setItem(8, 1, tempTable);

    tempTable = new QTableWidgetItem;
    //ui->stadiumInfoTable->insertRow(ui->stadiumInfoTable->rowCount());
    tempTable->setText(stadium->getRoofType());
    ui->stadiumInfoTable->setItem(9, 1, tempTable);
}

void InformationView::on_teamDropDown_currentTextChanged()
{
    int temp = ui->stadiumInfoTable->rowCount();
    for(int i = 0; i < temp; i++) {
        ui->stadiumInfoTable->removeRow(0);
    }
    createTable();
}

