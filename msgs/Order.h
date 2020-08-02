#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "Message.h"

class Order: public Message
{
    public:
        Order();
        Order ( const std::string& serial );

        void set_location ( int location );
        int get_location() const;
        void set_items ( const std::map<std::string, int>& items );
        std::map<std::string, int> get_items() const;

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        int location;
        std::map<std::string, int> items;
};

#endif
