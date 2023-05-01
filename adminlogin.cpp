#include "adminlogin.h"
#include "adminpage.h"
#include "ui_adminlogin.h"
#include <QLineEdit>
#include <QMessageBox>
AdminLogin::AdminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
    hidePassword = true;
    ui->passwordText->setEchoMode(QLineEdit::Password);
    QPixmap lockedPix(":/Icons/locked.png");
    ui->passViewButton->setIcon(lockedPix);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}



void AdminLogin::on_passViewButton_clicked()
{
    if (hidePassword == true)
    {
        hidePassword = false;
        ui->passwordText->setEchoMode(QLineEdit::Normal);
        QPixmap unlockedPix(":/Icons/unlocked.png");
        ui->passViewButton->setIcon(unlockedPix);
    }
    else
    {
        hidePassword = true;
        ui->passwordText->setEchoMode(QLineEdit::Password);
        QPixmap lockedPix(":/Icons/locked.png");
        ui->passViewButton->setIcon(lockedPix);
    }
}


void AdminLogin::on_loginButton_clicked()
{
    QString username = ui->usernameText->toPlainText();
    QString password = ui->passwordText->text();

    if (username == "" && password == "")
    {
        this->close();
        AdminPage adminPage;
        adminPage.setModal(true);
        adminPage.exec();
    }
    else
    {
        QMessageBox::information(this, "ERROR", "Incorrect username/password. Please try again.");
    }

}

