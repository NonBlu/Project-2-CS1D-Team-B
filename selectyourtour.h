#ifndef SELECTYOURTOUR_H
#define SELECTYOURTOUR_H

#include <QDialog>
#include "stadiummanager.h"

namespace Ui { class SelectYourTour; }

class SelectYourTour : public QDialog
{
    Q_OBJECT

public:
    explicit SelectYourTour(StadiumManager* sm, bool all, QWidget *parent = nullptr);

    ~SelectYourTour();

signals:
    void orderTypeChanged(QString value);

private slots:
    void on_nextButton_clicked();

    void on_doneButton_clicked();

    void on_specifiedButton_clicked();

    void on_efficientButton_clicked();

    void on_startingButton_clicked();

private:
    Ui::SelectYourTour* ui;
    StadiumManager*     sm;
    vector<QString> customTrip;
};

#endif // SELECTYOURTOUR_H
