#include "Order.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

const std::string Order::type = "o";

Order::Order()
{
}

Order::Order ( const std::string& serial )
{
    deserialize ( serial );
}

void Order::set_location ( int location )
{
    this->location = location;
}

int Order::get_location() const
{
    return location;
}

void Order::set_items ( const std::map<std::string, int>& items )
{
    this->items = items;
}

std::map<std::string, int> Order::get_items() const
{
    return items;
}

std::string Order::serialize() const{
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( location, items );
    }

    return type + ss.str();
}

void Order::deserialize ( const std::string& serial )
{
    // Read in new order
    std::stringstream ss ( serial.substr ( 1 ) );

    {
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive

        iarchive ( location, items ); // Read the data from the archive
    }
}
