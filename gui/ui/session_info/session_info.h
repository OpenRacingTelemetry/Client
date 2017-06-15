#pragma once

#include <QDialog>

#include "library/model/Race.h"

namespace Ui
{
    class Dialog;
}

class SessionInfo: public QDialog
{
    Q_OBJECT

public:
    explicit SessionInfo(Race* race, QWidget *parent = 0);
    ~SessionInfo();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    Race* race;
};
