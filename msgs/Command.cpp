#include "Command.h"

Command::Command(std::string command) {
    this->command = command;
}

std::string Command::get_serial() const {
    return "c" + command;
}

