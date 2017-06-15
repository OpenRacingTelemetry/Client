#include "settings.h"
#include "ui_settings.h"

SettingsUI::SettingsUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

SettingsUI::~SettingsUI()
{
    delete ui;
}

void SettingsUI::on_buttonBox_rejected()
{

}

void SettingsUI::on_buttonBox_accepted()
{

}
/*
 void MainWindow::ApiRefresh()
 {
    QList<QString> apis = DeviceApi::GetApiVersions();
    if(apis.length()>0)
    {

        for(int i=0;i<apis.count();i++)
        {
            ui->comboBox_connection_api->addItem(apis[i]);
        }
    }
 }
*/
