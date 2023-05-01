#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();


private slots:
    void on_passViewButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::AdminLogin *ui;
    bool hidePassword;
};

#endif // ADMINLOGIN_H
