#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Message.h"

class Command: public Message
{
    private:
        std::string command;
    public:
        Command ( std::string command );
        std::string get_serial() const override;
};

#endif
