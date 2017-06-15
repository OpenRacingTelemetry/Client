#include "SerialPort.h"

#include <QIODevice>
#include <QDebug>
#include <iostream>

SerialPort::SerialPort()
{
    qDebug()<<"SerialPort::Ctor()";
}

SerialPort::~SerialPort()
{
    qDebug()<<"SerialPort::Dtor()";

    disconnect(&serialPort, &QSerialPort::readyRead, this, &SerialPort::readToBufferSync);
    disconnect(&serialPort, static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error) , this, &SerialPort::errorHandle);
    disconnect(&serialPort, &QSerialPort::destroyed, this, &SerialPort::ClosePort);

    qDebug()<<"SerialPort::Emit-->sig_destroyed()";
    emit sig_destroyed();
}

void SerialPort::SetBaudRate(int baudRate)
{
    qDebug()<<"SerialPort::SetBaudRate()-->"<<baudRate;
    serialPort.setBaudRate(baudRate);
}

void SerialPort::SetPortName(QString portName)
{
    qDebug()<<"SerialPort::SetPortName()-->"<<portName;
    serialPort.setPortName(portName);
}

void SerialPort::SetPortInfo(QSerialPortInfo portInfo)
{
    qDebug()<<"SerialPort::SetPortInfo()";
    serialPort.setPortName(portInfo.portName());
}

void SerialPort::WriteSync(QByteArray data)
{
    qDebug()<<"SerialPort::WriteSync()";
    if(serialPort.isOpen())
    {
        serialPort.write(data);
    }
}

bool SerialPort::OpenPort(bool Read, bool Write)
{
    qDebug()<<"SerialPort::OpenPort()";
    QIODevice::OpenMode om;
    if(Write)
    {
        om=QIODevice::ReadWrite;
    }
    else
    {
        om=QIODevice::ReadOnly;
    }

    if (!serialPort.open(om)) {
            std::cout << QObject::tr("Failed to open port %1, error: %2")
                              .arg(serialPort.portName())
                              .arg(serialPort.error()).toStdString() << std::endl;
            return false;
    }

    qDebug()<<"SerialPort::Emit-->sig_port_open()";
    emit sig_port_open();

    connect(&serialPort, &QSerialPort::readyRead, this, &SerialPort::readToBufferSync);
    connect(&serialPort, static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error) , this, &SerialPort::errorHandle);
    connect(&serialPort, &QSerialPort::destroyed, this, &SerialPort::ClosePort);
    return true;
}

void SerialPort::ClosePort()
{
    if(serialPort.isOpen())
    {
        serialPort.close();
    }

    qDebug()<<"SerialPort::Emit-->sig_port_close()";
    emit sig_port_close();
}

QList<QSerialPortInfo> SerialPort::EnumeratePorts()
{
    return QSerialPortInfo::availablePorts();
}

QByteArray SerialPort::GetBuffer()
{
    QByteArray a2(serialBuffer);
    serialBuffer.clear();
    return a2;
}

void SerialPort::readToBufferSync()
{
    qDebug()<<"SerialPort::ReadToBufferSync()";
    int prbsize = serialBuffer.size();
    serialBuffer.append(QString::fromLocal8Bit(serialPort.readAll()));
    if(prbsize!=serialBuffer.size())
    {
        emit sig_data_readen();
    }
}

void SerialPort::errorHandle(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::NoError)
    {
        return;
    }

    qDebug()<<"SerialPort::errorHandle(): "<< error;
    emit sig_port_error(error);
}
