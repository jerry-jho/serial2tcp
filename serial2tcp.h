#ifndef SERIAL2TCP_H
#define SERIAL2TCP_H

#include <QtCore>
#include <QtSerialPort>
#include <QtNetwork>
#include <iostream>

class Serial2Tcp : public QObject
{
	Q_OBJECT

public:
	Serial2Tcp(QSerialPortInfo info,int serialBandRate,int tcpPort, QObject *parent = nullptr);

public slots:
	void startSlave();

private slots:
	void serialReadRequest();
	void tcpReadRequest();
	void newConnection();

private:
	void processError(const QString &s);

private:
	QSerialPortInfo m_serial_info;
	int m_serial_baudrate;
	int m_tcp_port;
	QSerialPort m_serial;
	QByteArray m_request;
	QTcpServer m_tcp_server;
	QTcpSocket * m_socket;

};

#endif // DIALOG_H