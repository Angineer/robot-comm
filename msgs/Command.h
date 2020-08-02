#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Message.h"

class Command: public Message
{
    public:
        Command();
        Command ( const std::string& serial );

        void set_command ( const std::string& command );
        std::string get_command() const;

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;

        std::string command;
};

#endif
