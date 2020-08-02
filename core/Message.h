#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message{
    public:
        // Generate a serialized string version of the message
        virtual std::string serialize() const = 0;

        // Generate the message from a serialized string
        virtual void deserialize ( const std::string& serial ) = 0;
};

#endif
