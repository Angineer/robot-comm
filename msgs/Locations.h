#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <string>
#include <vector>

#include "Message.h"

class Locations: public Message
{
    public:
        Locations();
        Locations ( const std::string& serial );

        std::vector<std::string> get_locations();

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        std::vector<std::string> locations;
};

#endif
