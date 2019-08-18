#include <QtCore>
#include <QtSerialPort>
#include <iostream>
#include "serial2tcp.h"


int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("serial2tcp");
	QCoreApplication::setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription("A server application that redirect serial port data to tcp network");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption serialPortNameOption(QStringList() << "s" << "serial-port",
		QLatin1Literal("select serial port <port>."),
		QLatin1Literal("port"));
	parser.addOption(serialPortNameOption);

	QCommandLineOption serialBaudRateOption(QStringList() << "b" << "baud-rate",
		QLatin1Literal("use baud rate <rate>."),
		QLatin1Literal("rate"),
		QLatin1Literal("115200"));
	parser.addOption(serialBaudRateOption);

	QCommandLineOption tcpPortOption(QStringList() << "p" << "server-port",
		QLatin1Literal("use server port <port>."),
		QLatin1Literal("port"),
		QLatin1Literal("9988"));
	parser.addOption(tcpPortOption);

	parser.process(app);

	const QStringList args = parser.positionalArguments();

	QString serialPortName = parser.value(serialPortNameOption);
	QSerialPortInfo serialPortInfo = QSerialPortInfo(serialPortName);
	if (serialPortInfo.isNull()) {
		std::cerr << "[ERROR] serial port not found: " << qPrintable(serialPortName) << std::endl;
		//parser.showHelp();
		return -1;
	}
	if (serialPortInfo.isBusy()) {
		std::cerr << "[ERROR] serial port is busy: " << qPrintable(serialPortName) << std::endl;
		return -1;
	}

	QString serialBaudRate = parser.value(serialBaudRateOption);
	bool ok;
	int iSerialBaudRate = serialBaudRate.toInt(&ok);
	if (!ok) {
		std::cerr << "[ERROR] baudrate: integer expected, recieve " << qPrintable(serialBaudRate) << std::endl;
		return -1;
	}

	QString tcpPort = parser.value(tcpPortOption);
	int iTcpPort = tcpPort.toInt(&ok);
	if (!ok || iTcpPort < 1000 || iTcpPort > 65535) {
		std::cerr << "[ERROR] server port: integer [1000,65535] expected, recieve " << qPrintable(serialBaudRate) << std::endl;
		return -1;
	}
	Serial2Tcp core(serialPortInfo, iSerialBaudRate, iTcpPort);
	core.startSlave();


	//std::cout << qPrintable(serialPortName) << std::endl;
	//std::cout << qPrintable(serialBaudRate) << std::endl;
	return app.exec();
}
