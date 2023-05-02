#include "selectyourtour.h"
#include "ui_selectyourtour.h"
#include <QMessageBox>
#include "tourpage.h"

SelectYourTour::SelectYourTour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectYourTour)
{
    ui->setupUi(this);
    ui->efficientButton->setVisible(false);
    ui->specifiedButton->setVisible(false);
    ui->orderLabel->setVisible(false);



    for(auto& mlb : sm.map) {
        QString stadiumName = mlb.getStadiumName();
        ui->nameDropdown->addItem(stadiumName);
    }

    ui->selectLabel->setText("Select the 1st Stadium\nYou Would Like to Visit:");
}

SelectYourTour::~SelectYourTour()
{
    delete ui;
}

void SelectYourTour::on_nextButton_clicked()
{
    QString temp = ui->nameDropdown->currentText();
    if (temp == "")
    {
        QMessageBox::information(this, "Error!", "There are no more stadiums to select. Please select \"Done\".");
        return;
    }
    customTrip.push_back(temp);
    int tripNum = customTrip.size() + 1;
    QString newLabel = "Select the " + QString::number(tripNum);
    if (tripNum == 2 || tripNum == 22)
    {
        newLabel+= "nd Stadium\nYou Would Like to Visit:";
    }
    else if (tripNum == 3 || tripNum == 23)
    {
        newLabel+= "rd Stadium\nYou Would Like to Visit:";
    }
    else if(tripNum == 21 || tripNum == 31)
    {
        newLabel+= "st Stadium\nYou Would Like to Visit:";
    }
    else
    {
        newLabel+= "th Stadium\nYou Would Like to Visit:";
    }
    ui->selectLabel->setText(newLabel);
    int currentIndex = ui->nameDropdown->currentIndex();
    ui->nameDropdown->removeItem(currentIndex);
    ui->nameDropdown->setCurrentIndex(0);

//    for(auto i: customTrip)
//    {
//        qDebug() << i;
//    }
}


void SelectYourTour::on_doneButton_clicked()
{
    if(customTrip.size() < 2)
    {
        QMessageBox::information(this, "Error!", "Please select at least two stadiums.");
        return;
    }
    ui->nextButton->setVisible(false);
    ui->doneButton->setVisible(false);
    ui->nameDropdown->setVisible(false);
    ui->selectLabel->setVisible(false);
    ui->efficientButton->setVisible(true);
    ui->specifiedButton->setVisible(true);
    ui->orderLabel->setVisible(true);
}


void SelectYourTour::on_specifiedButton_clicked()
{
    vector<QString> temp = customTrip;
    TourPage tourPage("Specified Order Tour", temp);
    tourPage.setModal(true);
    tourPage.exec();
}


void SelectYourTour::on_efficientButton_clicked()
{
    vector<QString> temp = customTrip;

    TourPage tourPage("Most Efficient Tour", temp);
    tourPage.setModal(true);
    tourPage.exec();
}

