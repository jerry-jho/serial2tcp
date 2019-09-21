# serial2tcp

A TCP Server that redirect serial port stream to tcp stream
Since many embedded system has only serial port as data transfer or terminal
This tiny server may make them remote accessable

# Requirements

Any platform that supports Qt5.2 or higher.

# Build

    qmake serial2tcp.pro CONFIG+=BUILD_DLL
    *make # depending on your build env
    qmake serial2tcp.pro CONFIG+=BUILD_APP
    *make # depending on your build env    
    
# Run

    serial2tcp -s <serial_port> -b <serial_baud_rate> -p <server_port>
    
# Test
    
    telnet <serial_ip> <server_port> 
