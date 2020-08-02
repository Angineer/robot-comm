#ifndef INVENTORY_MSG_H
#define INVENTORY_MSG_H

#include <map>
#include <string>

#include "Message.h"

class Inventory: public Message
{
    public:
        Inventory();
        Inventory ( const std::string& serial );

        void set_items ( const std::map<std::string, int>& items );
        std::map<std::string, int> get_items();

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        std::map<std::string, int> items;
};

#endif
