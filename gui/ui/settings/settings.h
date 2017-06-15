#pragma once

#include <QDialog>

namespace Ui {
    class Dialog;
}

class SettingsUI: public QDialog
{
    Q_OBJECT

public:
    explicit SettingsUI(QWidget *parent = 0);
    ~SettingsUI();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
};
