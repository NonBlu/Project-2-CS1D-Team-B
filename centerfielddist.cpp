#include "centerfielddist.h"
#include "ui_centerfielddist.h"

CenterFieldDist::CenterFieldDist(QString type, StadiumManager* sm, QWidget *parent) :
    QDialog(parent), ui(new Ui::CenterFieldDist), sm { sm }
{
    ui->setupUi(this);

    if(type == "greatest") {
        vector<QString> stadiums;
        int greatestFeet = 0;
        int greatestMeters = 0;

        ui->header->setText("Displaying Stadium(s) with \nGreatest Distance to Center Field");
        ui->header->setAlignment(Qt::AlignCenter);

        for(auto& mlb : sm->map) {
            if(mlb.getFeetToCenter() > greatestFeet) {
                greatestFeet = mlb.getFeetToCenter();
                greatestMeters = mlb.getMetersToCenter();
                stadiums.clear();
                stadiums.push_back(mlb.getStadiumName());
            }
            else if(mlb.getFeetToCenter() == greatestFeet) {
                stadiums.push_back(mlb.getStadiumName());
            }
        }

        ui->distanceLabel->setText("Greatest distance: "
                                   + QString::number(greatestFeet)
                                   + " feet or "
                                   + QString::number(greatestMeters) + " meters.");

        for(unsigned int i = 0; i < stadiums.size(); i++) {
            QListWidgetItem*temp = new QListWidgetItem;
            temp->setText(stadiums[i]);
            ui->stadiumList->insertItem(i, temp);
        }
    }
    else {
        vector<QString> stadiums;
        int smallestFeet = INT_MAX;
        int smallestMeters = INT_MAX;

        ui->header->setText("Displaying Stadium(s) with \nSmallest Distance to Center Field");
        ui->header->setAlignment(Qt::AlignCenter);

        for(auto& mlb : sm->map) {
            if(mlb.getFeetToCenter() < smallestFeet) {
                smallestFeet = mlb.getFeetToCenter();
                smallestMeters = mlb.getMetersToCenter();
                stadiums.clear();
                stadiums.push_back(mlb.getStadiumName());
            }
            else if(mlb.getFeetToCenter() == smallestFeet) {
                stadiums.push_back(mlb.getStadiumName());
            }
        }

        ui->distanceLabel->setText("Smallest distance: "
                                   + QString::number(smallestFeet)
                                   + " feet or "
                                   + QString::number(smallestMeters) + " meters.");

        for(unsigned int i = 0; i < stadiums.size(); i++) {
            QListWidgetItem*temp = new QListWidgetItem;
            temp->setText(stadiums[i]);
            ui->stadiumList->insertItem(i, temp);
        }
    }
}

CenterFieldDist::~CenterFieldDist()
{
    delete ui;
}
