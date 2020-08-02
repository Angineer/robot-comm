#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <string>

#include "Message.h"
#include "Socket.h"

class Client {
public:
    Client ( SocketType type, std::string connection_string );
    ~Client ();
    std::string send ( Message& message );

private:
    // Create a new socket using the connection info provided
    // @param type The type of socket to create
    // @param connectionString The type-specific connection info
    std::unique_ptr<Socket> createSocket ( 
        SocketType type, const std::string& connectionString );

    // Connect to the socket
    // @param socket The socket to which to connect
    int connectSocket ( const std::unique_ptr<Socket>& socket );

    // Recreate the socket and try to reconnect
    // @param msg A message string to print to the log about why we're
    //        reconnecting
    int resetConnection ( const std::string& msg );

    // Socket connection details
    SocketType m_Type;
    std::string m_ConnectionString;

    // Pointer to the actual socket
    std::unique_ptr<Socket> m_Socket;

    // Status of the socket connection
    int m_Connected;
};

#endif
