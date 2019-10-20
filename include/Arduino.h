#ifndef ARDUINO_H
#define ARDUINO_H

#include <string>

class Arduino {
public:
    Arduino ( std::string device );
    ~Arduino();

    // Send a single byte to the Arduino over serial
    bool sendByte ( char byte );
    bool sendByte ( int byte );

    // Read a single byte from the Arduino over serial
    char receiveByte();

private:
	// OS file descriptor from when we open the device
    int serial_fd;
};

#endif