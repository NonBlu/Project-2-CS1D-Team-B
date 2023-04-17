#ifndef INFORMATIONVIEW_H
#define INFORMATIONVIEW_H

#include <QDialog>

namespace Ui {
class InformationView;
}

class InformationView : public QDialog
{
    Q_OBJECT

public:
    explicit InformationView(QWidget *parent = nullptr);
    ~InformationView();

private:
    Ui::InformationView *ui;
};

#endif // INFORMATIONVIEW_H
