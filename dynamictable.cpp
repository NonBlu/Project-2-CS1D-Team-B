#include "dynamictable.h"
#include "ui_dynamictable.h"

DynamicTable::DynamicTable(StadiumManager* sm, QWidget *parent) :
    QDialog(parent), ui(new Ui::DynamicTable), sm { sm }
{
    ui->setupUi(this);

    QTableWidgetItem* tempTable;

    vector<QString> filterList = { "N/A", "American League", "National League", "Open Roof Type" };
    for(unsigned int a = 0; a < filterList.size(); a++) {
        ui->filterDropdown->addItem(filterList[a]);
    }

    vector<QString> sortList = { "N/A", "Stadium", "Team", "Park Typology", "Date Opened", "Seating Capacity" };
    for(unsigned int b = 0; b < sortList.size(); b++) {
        ui->sortDropdown->addItem(sortList[b]);
    }

    // ========================== Information Table ==========================
    // setting column count to 4
    ui->infoTable->setColumnCount(5);

    // making it so that end-user cannot edit
    ui->infoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // setting headers
    QStringList infoHeaders = { "Team Name", "Stadium Name", "Park Typology", "Date Opened", "Seating Capacity" };
    ui->infoTable->setHorizontalHeaderLabels(infoHeaders);

    // creating information table elements
    int i = 0;
    for(auto& mlb : sm->map) {
        // column 1: Team Name
        tempTable = new QTableWidgetItem;
        ui->infoTable->insertRow(ui->infoTable->rowCount()); // new row
        tempTable->setText(mlb.getTeamName());
        ui->infoTable->setItem(i, 0, tempTable);

        // column 2: Stadium Name
        tempTable = new QTableWidgetItem;
        tempTable->setText(mlb.getStadiumName());
        ui->infoTable->setItem(i, 1, tempTable);

        // column 3: Park Typology
        tempTable = new QTableWidgetItem;
        tempTable->setText(mlb.getTypology());
        ui->infoTable->setItem(i, 2, tempTable);

        // column 4: Date Opened
        tempTable = new QTableWidgetItem;
        tempTable->setText(QString::number(mlb.getDateOpened()));
        ui->infoTable->setItem(i, 3, tempTable);

        // column 5: Seating Capacity
        tempTable = new QTableWidgetItem;
        tempTable->setText(QString::number(mlb.getSeatingCapacity()));
        ui->infoTable->setItem(i, 4, tempTable);

        i++;    // incrementing row
    }

    ui->infoTable->setColumnHidden(2, true);    // Hiding Park Typology column
    ui->infoTable->setColumnHidden(3, true);    // Hiding Date Opened column
    ui->infoTable->setColumnHidden(4, true);    // Hiding Seating Capacity column
    ui->bottomLabel->hide();                    // Hiding Bottom Label

    ui->infoTable->resizeRowsToContents();
}

DynamicTable::~DynamicTable()
{
    delete ui;
}

void DynamicTable::on_filterDropdown_currentTextChanged(const QString &arg1)
{
    // Making all rows visible (resetting)
    for(int i = 0; i < ui->infoTable->rowCount(); i++) {
        ui->infoTable->setRowHidden(i, false);
    }

    QString currentText = ui->filterDropdown->currentText();

    if(currentText == "American League") {
        int teamNum = 0;
        for(int i = 0; i < ui->infoTable->rowCount(); i++) {
            MLB *stadium = sm->getStadium(ui->infoTable->item(i, 1)->text());

            if(stadium->getLeague() != "American") {
                ui->infoTable->setRowHidden(i, true);
            }
            else {
                teamNum += 1;
            }
        }
        ui->bottomLabel->show();
        ui->bottomLabel->setText("Total number of teams: " + QString::number(teamNum));
    }
    else if(currentText == "National League") {
        int teamNum = 0;
        for(int i = 0; i < ui->infoTable->rowCount(); i++) {
            MLB *stadium = sm->getStadium(ui->infoTable->item(i, 1)->text());

            if(stadium->getLeague() != "National") {
                ui->infoTable->setRowHidden(i, true);
            }
            else {
                teamNum += 1;
            }
        }
        ui->bottomLabel->show();
        ui->bottomLabel->setText("Total number of teams: " + QString::number(teamNum));
    }
    else if(currentText == "Open Roof Type") {
        int teamNum = 0;
        for(int i = 0; i < ui->infoTable->rowCount(); i++) {
            MLB *stadium = sm->getStadium(ui->infoTable->item(i, 1)->text());

            if(stadium->getRoofType() != "Open") {
                ui->infoTable->setRowHidden(i, true);
            }
            else {
                teamNum += 1;
            }
        }
        ui->bottomLabel->show();
        ui->bottomLabel->setText("Total number of teams: " + QString::number(teamNum));

    }
    else {
        ui->bottomLabel->hide();    // Hiding bottom label
        return; // For condition "N/A"
    }


}

void DynamicTable::on_sortDropdown_currentTextChanged(const QString &arg1)
{
    ui->infoTable->setColumnHidden(2, true);    // Hiding Park Typology column
    ui->infoTable->setColumnHidden(3, true);    // Hiding Date Opened column
    ui->infoTable->setColumnHidden(4, true);    // Hiding Seating Capacity column

    QString currentText = ui->sortDropdown->currentText();  // Retrieving text from dropdown

    if(currentText == "Stadium") {
        ui->infoTable->sortByColumn(1, Qt::AscendingOrder);
    }
    else if(currentText == "Team") {
        ui->infoTable->sortByColumn(0, Qt::AscendingOrder);
    }
    else if(currentText == "Park Typology") {
        ui->infoTable->setColumnHidden(2, false);
        ui->infoTable->sortByColumn(2, Qt::AscendingOrder);
    }
    else if(currentText == "Date Opened") {
        ui->infoTable->setColumnHidden(3, false);
        ui->infoTable->sortByColumn(3, Qt::AscendingOrder);
    }
    else if(currentText == "Seating Capacity") {
        ui->infoTable->setColumnHidden(4, false);
        ui->infoTable->sortByColumn(4, Qt::AscendingOrder);
        qlonglong totalCap = 0;
        bool ok;
        for(int i = 0; i < ui->infoTable->rowCount(); i++) {
            QString currentItem = ui->infoTable->item(i, 4)->text();
            totalCap += currentItem.toLongLong(&ok, 10);
        }

        ui->bottomLabel->setText("Total capacity of all stadiums: " + QString::number(totalCap));
        ui->bottomLabel->show();
    }
    else {
        ui->bottomLabel->hide();
        return; // For condition "N/A"
    }
}


void DynamicTable::on_greatestDistButton_clicked()
{
    CenterFieldDist dialog("greatest", sm);
    dialog.setModal(true);
    dialog.exec();
}


void DynamicTable::on_smallestDistButton_clicked()
{
    CenterFieldDist dialog("smallest", sm);
    dialog.setModal(true);
    dialog.exec();
}

