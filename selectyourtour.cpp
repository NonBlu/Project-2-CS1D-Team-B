#include "selectyourtour.h"
#include "ui_selectyourtour.h"
#include <QMessageBox>
#include "tourpage.h"
#include "mlb.h"
#include "stadiummanager.h"
SelectYourTour::SelectYourTour(StadiumManager* sm,bool all, QWidget *parent) :
    QDialog(parent), ui(new Ui::SelectYourTour), sm { sm }
{

    ui->setupUi(this);
    ui->efficientButton->setVisible(false);
    ui->specifiedButton->setVisible(false);
    ui->orderLabel->setVisible(false);

    vector<QString> temp;
    for(auto& mlb : sm->map)
    {
        temp.push_back(mlb.getTeamName());
    }

    sort(temp.begin(), temp.end());

    for(int i = 0; i < temp.size(); i++)
    {
        ui->nameDropdown->addItem(temp[i]);
    }

    if(!all)
    {
        ui->selectLabel->setText("Select the 1st Team"
                                 "\nYou Would Like to Visit:");
        ui->startingButton->setVisible(false);
    }
    else
    {
        ui->selectLabel->setText("Select Your"
                                 " Starting \n          Location");
        ui->nextButton->setVisible(false);
        ui->doneButton->setVisible(false);
    }
}

SelectYourTour::~SelectYourTour()
{
    delete ui;
}

void SelectYourTour::on_nextButton_clicked()
{
    MLB* tempMLB = sm->getTeam(ui->nameDropdown->currentText());
    QString temp = tempMLB->getStadiumName();
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
    if (customTrip.size() < 2)
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
    TourPage tourPage("Specified Order Tour", temp, sm);
    tourPage.setModal(true);
    tourPage.exec();
}


void SelectYourTour::on_efficientButton_clicked()
{
    vector<QString> temp = customTrip;

    TourPage tourPage("Most Efficient Tour", temp, sm);

    tourPage.setModal(true);

    tourPage.exec();
}


void SelectYourTour::on_startingButton_clicked()
{
    MLB* tempMLB = sm->getTeam(ui->nameDropdown->currentText());
    vector<QString> temp;
    temp.push_back(tempMLB->getStadiumName());

    TourPage tourPage("Visit All Stadiums", temp, sm);

    tourPage.setModal(true);

    tourPage.exec();
}

