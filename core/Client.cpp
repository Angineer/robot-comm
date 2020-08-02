#include "Client.h"

#include <iostream>
#include <netdb.h>
#include <csignal>
#include <string.h>
#include <unistd.h>

#include "BluetoothSocket.h"
#include "IpSocket.h"

Client::Client ( SocketType type, std::string connection_string ) :
    m_Type ( type ),
    m_ConnectionString ( connection_string ),
    m_Socket ( std::move ( createSocket ( m_Type, m_ConnectionString ) ) )
{
    if ( m_Socket ) {
        m_Connected = connectSocket ( m_Socket );    
    }

    // Handle broken pipes using program logic
    signal (SIGPIPE, SIG_IGN);;
}

Client::~Client() {
    if ( m_Socket ) {
        close ( m_Socket->socket_fd );
    }
}

std::string Client::send ( Message& message ){
    if ( !m_Socket || m_Connected < 0 ) {
        m_Connected = resetConnection ( "Client not connected!" );
        if ( !m_Connected ) {
            std::cout << "Client reconnected" << std::endl;
        } else {
            return "ERROR";
        }
    }

    message.write_serial();
    std::string content = message.get_serial();

    // First send the message length
    int len = content.length();
    int n = write(m_Socket->socket_fd, &len, sizeof(len));
    if (n <= 0) {
        m_Connected = 
            resetConnection ( "ERROR writing message length to socket" );
        return "ERROR";
    }

    // Then send the actual message
    n = write(m_Socket->socket_fd, content.c_str(), len);
    if (n <= 0) {
        m_Connected = resetConnection ( "ERROR writing message to socket" );
        return "ERROR";
    }

    // Read response length
    n = read(m_Socket->socket_fd, &len, sizeof(len));
    if (n <= 0) {
        m_Connected =
            resetConnection ( "ERROR reading response length from socket" );
        return "ERROR";
    } else {
        // Prep the buffer
        char buffer [len] = {};

        // Then read message
        n = read(m_Socket->socket_fd, buffer, len);
        if (n <= 0){
            m_Connected =
                resetConnection ( "ERROR reading response from socket" );
            return "ERROR";
        } else {
            std::string response(buffer, len);
            return response;
        }
    }
}

std::unique_ptr<Socket> Client::createSocket (
    SocketType type, const std::string& connectionString )
{
    std::unique_ptr<Socket> socket;
    if ( type == SocketType::IP ) {
        // Parse connection string
        size_t delim = connectionString.find ( ":" );
        std::string host = connectionString.substr ( 0, delim );
        std::string port = connectionString.substr ( delim + 1 );

        socket.reset ( new IpSocket ( host, std::stoi ( port ) ) );
    } else if ( type == SocketType::BLUETOOTH ) {
        socket.reset ( new BluetoothSocket ( connectionString ) );
    }

    if ( socket == nullptr ) {
        std::cout << "Client could not configure socket" << std::endl;
    }

    return socket;
}

int Client::connectSocket ( const std::unique_ptr<Socket>& socket )
{
    int connected = connect ( socket->socket_fd,
                              static_cast<sockaddr*> ( socket->address ),
                              socket->address_len );

    if ( connected < 0 ){
        std::cout << "Client failed to connect to server" << std::endl;
    }

    return connected;
}

int Client::resetConnection ( const std::string& msg )
{
    std::cout << "Resetting connection (" << msg << ")" << std::endl;
    if ( m_Socket ) {
        close ( m_Socket->socket_fd );
    }
    m_Socket = std::move ( createSocket ( m_Type, m_ConnectionString ) );
    return connectSocket ( m_Socket );
}
