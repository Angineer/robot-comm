#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <map>
#include <string>

#include "Message.h"

class Locations: public Message
{
    public:
        Locations();
        Locations ( const std::string& serial );

        void set_locations ( const std::map<int, std::string>& locations );
        std::map<int, std::string> get_locations();

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        std::map<int, std::string> locations;
};

#endif
