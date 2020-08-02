#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "Message.h"

class Order: public Message
{
    public:
        Order ( std::string location,
                std::map<std::string, int> items );

        std::string get_location();
        std::map<std::string, int> get_order();
        std::string get_serial() const override;
    private:
        std::string location;
        std::map<std::string, int> items;
};

#endif
