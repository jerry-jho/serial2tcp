#include "serial2tcp.h"

Serial2Tcp::Serial2Tcp(QSerialPortInfo info, int serialBandRate, int tcpPort, QObject *parent) :
	QObject(parent),
	m_serial_info(info),
	m_serial_baudrate(serialBandRate),
	m_tcp_port(tcpPort),
	m_socket(new QTcpSocket())
{
	connect(&m_serial, &QSerialPort::readyRead, this, &Serial2Tcp::serialReadRequest);
	connect(&m_tcp_server, &QTcpServer::newConnection, this, &Serial2Tcp::newConnection);
}

void Serial2Tcp::startSlave() {
	m_serial.setPortName(m_serial_info.portName());
	m_serial.setBaudRate(m_serial_baudrate);
	m_serial.setParity(QSerialPort::NoParity);
	m_serial.setStopBits(QSerialPort::OneStop);
	m_serial.setDataBits(QSerialPort::Data8);
	if (!m_serial.open(QIODevice::ReadWrite)) {
		processError(tr("Can't open %1, error code %2")
			.arg(m_serial.portName()).arg(m_serial.error()));
		return;
	}
	std::cout << "[INFO] Monitoring port " << qPrintable(m_serial_info.portName()) << " at " << m_serial_baudrate << std::endl;
	
	if (!m_tcp_server.listen(QHostAddress::Any, m_tcp_port)) {
		processError(tr("Can't listen on %1, error code %2")
			.arg(m_tcp_port).arg(m_tcp_server.errorString()));
		return;
	}
	std::cout << "[INFO] Server start on port " << m_tcp_port << std::endl;

	std::flush(std::cout);
}

void Serial2Tcp::serialReadRequest() {
	if (m_socket->isOpen()) {
		m_socket->write(m_serial.readAll());
	}
}

void Serial2Tcp::tcpReadRequest() {
	m_serial.write(m_socket->readAll());
}

void Serial2Tcp::newConnection() {
	if (m_socket->isValid()) {
		std::cout << "[INFO] Disconnect previous tcp socket" << std::endl;
		std::flush(std::cout);
		m_socket->disconnectFromHost();
	}
	std::cout << "[INFO] New tcp socket" << std::endl;
	std::flush(std::cout);
	m_socket = m_tcp_server.nextPendingConnection();
	connect(m_socket, &QAbstractSocket::disconnected,m_socket, &QObject::deleteLater);
	connect(m_socket, &QAbstractSocket::readyRead, this, &Serial2Tcp::tcpReadRequest);
}

void Serial2Tcp::processError(const QString & s) {
	std::cerr << "[ERROR] " << qPrintable(s) << std::endl;
	QCoreApplication::exit();
}
