#pragma once

#include <QAbstractItemModel>
#include <QWidget>
#include <QSerialPort>
#include <QTimer>
#include <QDateTime>

#include "library/model/Race.h"

namespace Ui {
    class Form;
}

class SessionWindow: public QWidget
{
    Q_OBJECT

public:
    explicit SessionWindow(QWidget *parent = 0);
    ~SessionWindow();

private slots:
    void on_pushButton_connection_connect_clicked();
    void on_pushButton_connection_disconnect_clicked();
    void on_pushButton_connection_refresh_clicked();

    void on_comboBox_connection_interface_currentIndexChanged(int index);

    void slot_PortClose();
    void slot_PortOpen();
    void slot_PortError(const QSerialPort::SerialPortError& error);
    void slot_PortDataRecieved();
    void slot_TimerTimeout();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_tableWidget_cellChanged(int row, int column);
    void on_tableWidget_rowsInserted(QModelIndex parent, int first, int last);

    void on_pushButton_info_savetoxlsx_clicked();

    void on_pushButton_info_close_clicked();

    void on_pushButton_editInfo_clicked();

    void on_pushButton_publish_clicked();

private:
    Ui::Form *ui;
    Race* race;
    QTimer timer;
    QDateTime lastsignaltime;

    void Initialize();
    void InterfaceRefresh();
};
