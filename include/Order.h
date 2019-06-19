#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "Message.h"

class Order: public Message
{
    public:
        Order ( std::map<std::string, int> items );

        std::map<std::string, int> get_order();
        void write_serial();
    private:
        std::map<std::string, int> items;
};

#endif
