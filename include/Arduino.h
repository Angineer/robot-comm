#ifndef ARDUINO_H
#define ARDUINO_H

#include <string>

class Arduino {
public:
    Arduino ( const std::string& device );
    ~Arduino();

    // Send a single byte to the Arduino over serial
    bool sendByte ( char byte );
    bool sendByte ( int byte );

    // Read a single byte from the Arduino over serial
    char receiveByte();

private:
    // The device where the Arduino is connected (e.g. /dev/ttyACM0)
    std::string device;

	// OS file descriptor from when we open the device
    int serial_fd;

    // Connect to the hardware
    // @param timeout_ds The timeout in deciseconds for a read over the serial
    //        port. By default, set a timeout of 20 sec. This is necessary 
    //        because we wait for a response after a dispense to let us know
    //        the hardware is done.
    void connect ( const std::string& device,
                   unsigned int timeout_ds = 200 );

    // Disconnect from the hardware
    void disconnect();
};

#endif
