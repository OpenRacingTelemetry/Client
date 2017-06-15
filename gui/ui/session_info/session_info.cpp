#include "session_info.h"
#include "ui_session_info.h"

#include "gui/ui/session/session.h"

#include "library/model/Race.h"

SessionInfo::SessionInfo(Race* race, QWidget *parent) : QDialog(parent), ui(new Ui::Dialog)
{
    this->race = race;
    ui->setupUi(this);

    ui->lineEdit_name->setText(race->GetName());
    ui->lineEdit_date->setText(race->GetDate());
    ui->plainTextEdit_comments->document()->setPlainText(race->GetDescription());
    ui->plainTextEdit_weather->document()->setPlainText(race->GetWeather());
}

SessionInfo::~SessionInfo()
{
    delete ui;
}

void SessionInfo::on_buttonBox_rejected()
{
    this->close();
}

void SessionInfo::on_buttonBox_accepted()
{
    race->SetName(ui->lineEdit_name->text());
    race->SetDescription(ui->plainTextEdit_comments->toPlainText());
    race->SetDate(ui->lineEdit_date->text());
    race->SetWeather(ui->plainTextEdit_weather->toPlainText());
    this->close();
}
