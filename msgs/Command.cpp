#include "Command.h"

const std::string Command::type = "c";

Command::Command()
{
}

Command::Command ( const std::string& serial )
{
    deserialize ( serial );
}

void Command::set_command ( const std::string& command )
{
    this->command = command;
}

std::string Command::get_command() const
{
    return command;
}

std::string Command::serialize() const {
    return type + command;
}

void Command::deserialize ( const std::string& serial )
{
    command = type + serial.substr ( 1 );
}
