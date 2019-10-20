#include "Arduino.h"

#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

Arduino::Arduino ( std::string device ) :
    serial_fd ( -1 )
{
    serial_fd = open ( device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY );
    if ( serial_fd == -1 ) {
        std::cout << "Unable to connect to Arduino" << std::endl;
    } else {
        fcntl(serial_fd, F_SETFL, 0);
        std::cout << "Arduino connected" << std::endl;
    }

    // Set serial port options
    struct termios options;

    // Get current options
    tcgetattr(serial_fd, &options);

    // Set baud rate
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // 8N1
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Timeout of 20 sec. This is necessary because we wait for a response
    // after a dispense to let us know the hardware is done.
    options.c_cc[VTIME] = 200;
    options.c_cc[VMIN] = 0;

    /* set the options */
    tcsetattr(serial_fd, TCSANOW, &options);
}

Arduino::~Arduino(){
    close ( serial_fd );
}

bool Arduino::sendByte ( char byte ) {
    if ( serial_fd > 0) {
        write ( serial_fd, &byte, 1 );
        return true;
    } else {
        std::cout << "Arduino disconnected!" << std::endl;
        return false;
    }
}

bool Arduino::sendByte ( int byte ) {
    return sendByte ( static_cast<char> ( byte ) );
}

char Arduino::receiveByte() {
    if ( serial_fd > 0) {
        char byte;
        read ( serial_fd, &byte, 1 );
        return byte;
    } else {
        std::cout << "Arduino disconnected!" << std::endl;
        return '\0';
    }
}
