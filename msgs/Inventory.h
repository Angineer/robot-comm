#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>

#include "Message.h"

class Inventory: public Message
{
    public:
        Inventory ( std::map<std::string, int> items );

        std::map<std::string, int> get_items();
        std::string get_serial() const override;

    private:
        std::map<std::string, int> items;
};

#endif
