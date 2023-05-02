#ifndef INFORMATIONVIEW_H
#define INFORMATIONVIEW_H

#include <QDialog>
#include "stadiummanager.h"

using namespace std;

namespace Ui { class InformationView; }

class InformationView : public QDialog
{
    Q_OBJECT

public:
    explicit InformationView(StadiumManager* sm, QWidget *parent = nullptr);
    ~InformationView();

private slots:
    void on_teamDropDown_currentTextChanged();
    void createTable();

private:
    Ui::InformationView *ui;
    StadiumManager* sm;
    vector<QString> infoType = {"Stadium Name", "Seating Capacity", "Location", "Playing Surface", "League", "Date Opened", "Distance to Center Field (feet)", "Distance to Center Field (meters)", "Ballpark typology", "Roof Type"};
};

#endif // INFORMATIONVIEW_H
