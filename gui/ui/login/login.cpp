#include "login.h"
#include "ui_login.h"

#include "gui/ui/session/session.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);

    nc = NetworkClient::instance();
    connect(nc,&NetworkClient::authFail,this,&LoginWindow::on_login_fail);
    connect(nc,&NetworkClient::authSuccess,this,&LoginWindow::on_login_success);
}

LoginWindow::~LoginWindow()
{

}


void LoginWindow::on_label_go_offline_clicked()
{
    (new SessionWindow())->show();
}

void LoginWindow::on_pushButton_login_clicked()
{
    nc->DoAuth(ui->lineEdit_login->text(),ui->lineEdit_password->text());
}

void LoginWindow::on_login_fail(QString msg)
{
    QMessageBox::critical(this,"Login error",msg,QMessageBox::Ok);
}

void LoginWindow::on_login_success()
{
    (new SessionWindow())->show();
}
