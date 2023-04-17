#ifndef TOURPAGE_H
#define TOURPAGE_H

#include <QDialog>

namespace Ui {
class TourPage;
}

class TourPage : public QDialog
{
    Q_OBJECT

public:
    explicit TourPage(QWidget *parent = nullptr);
    ~TourPage();

private slots:
    void on_souvenirButton_clicked();

    void on_recieptButton_clicked();

private:
    Ui::TourPage *ui;
};

#endif // TOURPAGE_H
