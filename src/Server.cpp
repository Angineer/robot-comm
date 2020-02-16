#include "Server.h"

#include <iostream>
#include <thread>
#include <unistd.h>

#include "BluetoothSocket.h"
#include "IpSocket.h"

Server::Server ( SocketType type )
{
    //serv_addr.sin_addr.s_addr = INADDR_ANY;
    if ( type == SocketType::IP ) {
        socket.reset ( new IpSocket() );
    } else if ( type == SocketType::BLUETOOTH ) {
        socket.reset ( new BluetoothSocket() );
    }

    // If socket not configured, exit
    if ( !socket ) {
        std::cout << "Server socket not configured!" << std::endl;
        return;
    }

    // Allow binding to the socket even if a previous instance of the server
    // went down while a client was still connected. Otherwise, we would have to
    // wait for the socket timeout before reconnecting.
    int val { 1 };
    setsockopt ( socket->socket_fd,
                 SOL_SOCKET,
                 SO_REUSEADDR,
                 &val,
                 sizeof ( val ) );

    int bind_success = bind ( socket->socket_fd, 
                              static_cast<sockaddr*> ( socket->address ),
                              socket->address_len );

    if ( bind_success < 0 ) {
        std::cout << "ERROR binding to socket! " << errno << std::endl;
        exit(1);
    }
}

Server::~Server() {
    if ( socket ) {
        close ( socket->socket_fd );
    }
}

void Server::child_serve(int sockfd, std::function<std::string ( std::string )> callback_func){
    int len;

    std::cout << "Child thread started!" << std::endl;

    // Process data until disconnect
    bool connect = true;
    while(connect){
        // Read length of message from socket
        int n = read(sockfd, &len, sizeof(len));
        if (n < 0){
            std::cout << "ERROR reading from socket!" << std::endl;
        }
        else if(n == 0){
            close(sockfd);
            std::cout << "Connection " << sockfd << " disconnected!" << std::endl;
            connect = false;
        }
        else{
            // Prep the buffer
            char buffer [len] = {};

            // Then read message
            n = read(sockfd, buffer, len);
            if (n < 0){
                std::cout << "ERROR reading from socket!" << std::endl;
            }
            else if (n == 0){
                close(sockfd);
                std::cout << "Connection " << sockfd << " disconnected!" << std::endl;
                connect = false;
            }
            else{
                // Call callback using input
                std::string message ( buffer, len );
                std::string response = callback_func ( message );

                // Send response length
                len = response.length();
                n = ::write(sockfd, &len, sizeof(len));
                if (n < 0)
                     std::cout << "ERROR writing to socket" << std::endl;

                // Then send the actual message
                n = ::write(sockfd, response.c_str(), len);
                if (n < 0)
                     std::cout << "ERROR writing to socket" << std::endl;
            }
        }
    }
}

void Server::serve ( std::function<std::string ( std::string )> callback_func ) {
    std::cout << "Listening for connections" << std::endl;
    
    if ( listen ( socket->socket_fd, 5 ) ) {
        std::cout << "Failed to listen on socket! " << errno << std::endl;
        return;
    }

    // Server runs forever
    while ( true ) {
        sockaddr client;
        socklen_t client_len = socket->address_len;
        int newsockfd = accept ( socket->socket_fd,
                                 &client,
                                 &client_len );

        if ( newsockfd > 0 ) {
            std::cout << "Connection " << newsockfd
                      << " established!" << std::endl;

            // Create child thread
            std::thread t ( &Server::child_serve,
                            this, newsockfd, callback_func );
            t.detach();
        }
    }
}
