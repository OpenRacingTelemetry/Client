#include "session.h"
#include "ui_session.h"

#include "gui/ui/session_info/session_info.h"

#include "library/device/SerialPort.h"

#include "library/network/ServerClient.h"

#include <QDebug>
#include <QTime>
#include <QFileDialog>
#include <QDesktopServices>

#include "3rdparty/libxlsx/xlsxdocument.h"

SessionWindow::SessionWindow(QWidget *parent) : QWidget(parent), ui(new Ui::Form)
{
    ui->setupUi(this);
    this->race = new Race();
    Initialize();
}


SessionWindow::~SessionWindow()
{
    SerialPort::Instance().ClosePort();

    disconnect(&(SerialPort::Instance()),&SerialPort::sig_data_readen,this,&SessionWindow::slot_PortDataRecieved);
    disconnect(&(SerialPort::Instance()),&SerialPort::sig_port_open,this,&SessionWindow::slot_PortOpen);
    disconnect(&(SerialPort::Instance()),&SerialPort::sig_port_close,this,&SessionWindow::slot_PortClose);
    disconnect(&(SerialPort::Instance()),&SerialPort::sig_port_error,this,&SessionWindow::slot_PortError);
    disconnect(&timer,&QTimer::timeout,this,&SessionWindow::slot_TimerTimeout);

    disconnect(ui->tableWidget->model(),&QAbstractItemModel::rowsInserted,this,&SessionWindow::on_tableWidget_rowsInserted);

    delete ui;
}

void SessionWindow::Initialize()
{
    ui->pushButton_connection_connect->setEnabled(false);
    ui->pushButton_connection_disconnect->setEnabled(false);
    ui->label_connection_status->setText(tr("Disconnected"));
    ui->label_connection_lastSignal->setText("");

    ui->label_info_eventName->setText(race->GetName());
    //ui->lavel_info_location->setText(race->GetLocation());

    connect(&(SerialPort::Instance()),&SerialPort::sig_data_readen,this,&SessionWindow::slot_PortDataRecieved);
    connect(&(SerialPort::Instance()),&SerialPort::sig_port_open,this,&SessionWindow::slot_PortOpen);
    connect(&(SerialPort::Instance()),&SerialPort::sig_port_close,this,&SessionWindow::slot_PortClose);
    connect(&(SerialPort::Instance()),&SerialPort::sig_port_error,this,&SessionWindow::slot_PortError);

    connect(ui->tableWidget->model(),&QAbstractItemModel::rowsInserted,this,&SessionWindow::on_tableWidget_rowsInserted);
    ui->tableWidget->insertRow(0);

    timer.setInterval(500);
    connect(&timer,&QTimer::timeout,this,&SessionWindow::slot_TimerTimeout);
    InterfaceRefresh();
}



void SessionWindow::InterfaceRefresh()
{
    QComboBox* control = ui->comboBox_connection_interface;
    QString selectedInterface = control->currentText();
    control->clear();

    QList<QSerialPortInfo> serialPorts = SerialPort::EnumeratePorts();

    if(serialPorts.length()==0)
    {
        ui->pushButton_connection_connect->setEnabled(false);
    }
    else
    {
        ui->pushButton_connection_connect->setEnabled(true);
        int selectedIndex = -1;

        for(int i=0;i<serialPorts.count();i++)
        {
            if(serialPorts[i].portName()==selectedInterface)
            {
                selectedIndex=i;
            }
            control->addItem(serialPorts[i].portName(),QVariant::fromValue(serialPorts[i]));
        }

        if(selectedIndex != -1)
        {
            control->setCurrentIndex(selectedIndex);
        }
    }
}

void SessionWindow::on_pushButton_connection_connect_clicked()
{
    if(!SerialPort::Instance().OpenPort(true,false))
    {
        return;
    }

    ui->pushButton_connection_connect->setEnabled(false);
    ui->pushButton_connection_refresh->setEnabled(false);
    ui->pushButton_connection_disconnect->setEnabled(true);
    ui->comboBox_connection_interface->setEnabled(false);

    lastsignaltime=QDateTime::currentDateTimeUtc();
    timer.start();
}

void SessionWindow::on_pushButton_connection_disconnect_clicked()
{
    SerialPort::Instance().ClosePort();

    timer.stop();
    ui->pushButton_connection_connect->setEnabled(true);
    ui->pushButton_connection_disconnect->setEnabled(false);
    ui->pushButton_connection_refresh->setEnabled(true);
    ui->comboBox_connection_interface->setEnabled(true);
    ui->label_connection_lastSignal->setText("");
}

void SessionWindow::on_comboBox_connection_interface_currentIndexChanged(int index)
{
    SerialPort::Instance().SetPortInfo(ui->comboBox_connection_interface->itemData(index).value<QSerialPortInfo>());
}

void SessionWindow::on_pushButton_connection_refresh_clicked()
{
    InterfaceRefresh();
}

void SessionWindow::slot_PortOpen(){
    ui->label_connection_status->setText(tr("Connected"));
}


void SessionWindow::slot_PortClose(){
    ui->label_connection_status->setText(tr("Disconnected"));
}

void SessionWindow::slot_PortError(const QSerialPort::SerialPortError& error)
{
    ui->label_connection_status->setText(tr("Error"));
}

void SessionWindow::slot_PortDataRecieved()
{
    QByteArray buffer = SerialPort::Instance().GetBuffer();
    qDebug()<<buffer;

    for(int i=0;i<buffer.length();i++)
    {
        if(i>1 && buffer[i]==buffer[i-1])
        {
            continue;
        }

        int index=0;
        int rowCount = ui->tableWidget->rowCount();
        for(int j=rowCount-1;j>=0;j--)
        {
            auto item = ui->tableWidget->item(j,(buffer[i]=='1')?0:1);
            if(item==nullptr)
            {
                continue;
            }
            else
            {
                index=j+1;
                break;
            }
        }

        if(index>=rowCount)
        {
            ui->tableWidget->insertRow(rowCount);
        }
        ui->tableWidget->setItem(index,(buffer[i]=='1')?0:1,new QTableWidgetItem(QDateTime::currentDateTime().toString("HH:mm:ss,zzz")));
    }

    lastsignaltime=QDateTime::currentDateTimeUtc();
}

void SessionWindow::slot_TimerTimeout()
{
    ui->label_connection_lastSignal->setText(QString::number(lastsignaltime.secsTo(QDateTime::currentDateTimeUtc()))+tr(" s"));
}


void SessionWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    int rowCount = ui->tableWidget->rowCount();
    if (index.row() == rowCount - 1)
    {
        ui->tableWidget->insertRow(rowCount);
    }
}

void SessionWindow::on_tableWidget_cellChanged(int row, int column)
{
    if( (column==2) || (column==4))
    {
        return;
    }


    if((ui->tableWidget->item(row,0)!=nullptr) && (ui->tableWidget->item(row,1)!=nullptr))
    {
        auto time_one = QDateTime::fromString(ui->tableWidget->item(row,0)->text(),"HH:mm:ss,zzz");
        auto time_two = QDateTime::fromString(ui->tableWidget->item(row,1)->text(),"HH:mm:ss,zzz");

        qint64 delta = time_one.msecsTo(time_two);
        if(delta<0)
        {
            delta=0;
        }

        ui->tableWidget->setItem(row,2,new QTableWidgetItem(QTime::fromMSecsSinceStartOfDay(delta).toString("HH:mm:ss,zzz")));

        if((ui->tableWidget->item(row,3)!=nullptr))
        {
             auto time_total = QTime::fromString(ui->tableWidget->item(row,2)->text(),"HH:mm:ss,zzz");
             auto time_penalty = QTime::fromString(ui->tableWidget->item(row,3)->text(),"HH:mm:ss,zzz");
             ui->tableWidget->setItem(row,4,new QTableWidgetItem(QTime::fromMSecsSinceStartOfDay(time_total.msecsSinceStartOfDay()+time_penalty.msecsSinceStartOfDay()).toString("HH:mm:ss,zzz")));
        }
    }
}

void SessionWindow::on_tableWidget_rowsInserted(QModelIndex parent, int first, int last)
{
    for(int i=first;i<=last;i++)
    {
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QTime::fromMSecsSinceStartOfDay(0).toString("HH:mm:ss,zzz")));
    }
}

void SessionWindow::on_pushButton_info_savetoxlsx_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Report"), "",
            tr("Microsoft Excel 2007-2016 files (*.xlsx)"));

    if(fileName.isEmpty())
    {
        return;
    }

    QXlsx::Document xlsx;

    //report info
    xlsx.addSheet(tr("Info")    );
    xlsx.write("A1", tr("Event"));
    xlsx.write("B1", race->GetName());

    //xlsx.write("A2", tr("Location"));
    //xlsx.write("B2", race->GetLocation());

    xlsx.write("A3", tr("Description"));
    xlsx.write("B3", race->GetDescription());

    xlsx.write("A4", tr("Weather"));
    xlsx.write("B4", race->GetWeather());

    xlsx.write("A5", tr("Report generation date"));
    xlsx.write("B5", QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm t"));

    xlsx.setColumnWidth(1,25);
    xlsx.setColumnWidth(2,35);

    //data
    xlsx.addSheet(tr("Data"));

    //data->header
    xlsx.write("A1",tr("Start time"));
    xlsx.setColumnWidth(1,15);

    xlsx.write("B1",tr("End time"));
    xlsx.setColumnWidth(2,15);

    xlsx.write("C1",tr("Result"));
    xlsx.setColumnWidth(3,15);

    xlsx.write("D1",tr("Penalty"));
    xlsx.setColumnWidth(4,15);

    xlsx.write("E1",tr("Total result"));
    xlsx.setColumnWidth(5,15);

    xlsx.write("F1",tr("Racer"));
    xlsx.setColumnWidth(6,15);

    xlsx.write("G1",tr("Comments"));
    xlsx.setColumnWidth(7,15);

    auto table = ui->tableWidget;
    for(int i =0;i<table->rowCount();i++)
    {
        for(int j=0;j<7;j++)
        {
            if(table->item(i,j)!=nullptr)
            {
                xlsx.write(i+2,j+1,table->item(i,j)->text());
            }
        }
    }

    xlsx.saveAs(fileName);
    QDesktopServices::openUrl(QUrl(fileName));
}

void SessionWindow::on_pushButton_info_close_clicked()
{
    this->close();
}

void SessionWindow::on_pushButton_editInfo_clicked()
{
    (new SessionInfo(this->race))->show();
}

void SessionWindow::on_pushButton_publish_clicked()
{
    auto sc = ServerClient::instance();
    sc->CreateRace(this->race);

    for(int row=0;row<ui->tableWidget->rowCount();row++)
    {
        Record r;

        if(ui->tableWidget->item(row,0)!=nullptr)
            r.SetTimeStart(QDateTime::fromString(ui->tableWidget->item(row,0)->text(),"HH:mm:ss,zzz"));

        if(ui->tableWidget->item(row,1)!=nullptr)
            r.SetTimeEnd(QDateTime::fromString(ui->tableWidget->item(row,1)->text(),"HH:mm:ss,zzz"));

        if(ui->tableWidget->item(row,3)!=nullptr)
            r.SetTimePenalty(QDateTime::fromString(ui->tableWidget->item(row,3)->text(),"HH:mm:ss,zzz"));

        if((ui->tableWidget->item(row,5)!=nullptr)&&(ui->tableWidget->item(row,6)!=nullptr))
            r.SetNotes(ui->tableWidget->item(row,5)->text()+"|"+ui->tableWidget->item(row,6)->text());

        sc->CreateRecord(this->race,&r);
    }
}
