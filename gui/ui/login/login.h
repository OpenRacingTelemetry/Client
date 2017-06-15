#pragma once

#include <QAbstractItemModel>
#include <QWidget>

#include "library/network/NetworkClient.h"

namespace Ui {
    class LoginForm;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_label_go_offline_clicked();

    void on_pushButton_login_clicked();

    void on_login_fail(QString msg);
    void on_login_success();

private:
    Ui::LoginForm *ui;
    NetworkClient *nc;
};

