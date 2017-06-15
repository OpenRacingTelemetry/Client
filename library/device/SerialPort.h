#pragma once

#include <QList>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#include "libtelemetry_export.h"

class LIBTELEMETRY_EXPORT SerialPort : public QObject
{
   Q_OBJECT

public:
    static SerialPort& Instance()
    {
        static SerialPort singleton;
        return singleton;
    }
    bool OpenPort(bool Read, bool Write);

    void ClosePort();

    static QList<QSerialPortInfo> EnumeratePorts();

    QByteArray GetBuffer();

    void SetBaudRate(int baudRate);
    void SetPortName(QString portName);
    void SetPortInfo(QSerialPortInfo portInfo);

    void WriteSync(QByteArray data);



signals:

    void sig_destroyed();
    void sig_port_close();
    void sig_port_open();
    void sig_data_written();
    void sig_data_readen();

    void sig_port_error(const QSerialPort::SerialPortError&);

private slots:
    void readToBufferSync();
    void errorHandle(QSerialPort::SerialPortError error);

private:
    SerialPort();
    ~SerialPort();

    SerialPort(const SerialPort&);                 // Prevent copy-construction
    SerialPort& operator=(const SerialPort&);      // Prevent assignment

    QSerialPort serialPort;
    QByteArray serialBuffer;


};

Q_DECLARE_METATYPE(QSerialPortInfo)
