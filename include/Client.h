#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <string>

#include "Message.h"
#include "Socket.h"

class Client
{
public:
    Client ( SocketType type, std::string connection_string );
    ~Client ();
    std::string send ( Message& message );

private:
    // Pointer to the actual socket
    std::unique_ptr<Socket> socket;

    // Status of the socket connection
    int connected;
};

#endif
