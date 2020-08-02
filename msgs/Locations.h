#ifndef LOCATIONS_H
#define LOCATIONS_H

#include <string>
#include <vector>

#include "Message.h"

class Locations: public Message
{
    public:
        Locations ( std::vector<std::string> location );

        std::vector<std::string> get_locations();
        std::string get_serial() const override;
    private:
        std::vector<std::string> locations;
};

#endif
