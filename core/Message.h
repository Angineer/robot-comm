#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

class Message{
    public:
        virtual std::string get_serial() const = 0;
};

#endif
