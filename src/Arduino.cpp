#include "Arduino.h"

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

Arduino::Arduino ( const std::string& device ) :
    device ( device ),
    serial_fd ( -1 )
{
    // Connect with the standard timeout
    connect ( device );
}

Arduino::~Arduino(){
    disconnect();
}

void Arduino::connect ( const std::string& device, unsigned int timeout_ds )
{
    serial_fd = open ( device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
    if ( serial_fd == -1 ) {
        std::cout << "Unable to connect to Arduino" << std::endl;
    } else {
        // Clear file status flags
        fcntl ( serial_fd, F_SETFL, 0 );
        std::cout << "Arduino connected" << std::endl;
    }

    // Set serial port options
    struct termios options;

    // Get current options
    tcgetattr(serial_fd, &options);

    // Set baud rate
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // Use "raw mode"
    cfmakeraw ( &options );

    // 8N1
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Set read timeouts
    options.c_cc[VTIME] = timeout_ds;
    options.c_cc[VMIN] = 0;

    /* set the options */
    tcsetattr(serial_fd, TCSANOW, &options);
}

void Arduino::disconnect()
{
    close ( serial_fd );
}

bool Arduino::sendByte ( char byte ) {
    if ( serial_fd > 0) {
        write ( serial_fd, &byte, 1 );
        return true;
    } else {
        std::cout << "Arduino disconnected! Reconnecting..." << std::endl;
        connect ( device );
        return false;
    }
}

bool Arduino::sendByte ( int byte ) {
    return sendByte ( static_cast<char> ( byte ) );
}

char Arduino::receiveByte() {
    char byte { '\0' };
    if ( serial_fd > 0 ) {
        read ( serial_fd, &byte, 1 );
    } else {
        std::cout << "Arduino disconnected! Reconnecting..." << std::endl;
        connect ( device );
    }
    return byte;
}
