#include "InventoryMsg.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

const std::string InventoryMsg::type = "i";

InventoryMsg::InventoryMsg()
{
}

InventoryMsg::InventoryMsg ( const std::string& serial )
{
    deserialize ( serial );
}

void InventoryMsg::set_items ( const std::map<std::string, int>& items )
{
    this->items = items;
}

std::map<std::string, int> InventoryMsg::get_items(){
    return items;
}

std::string InventoryMsg::serialize() const
{
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( items );
    }

    return type + ss.str();
}

void InventoryMsg::deserialize ( const std::string& serial )
{
    // Read in new order
    std::stringstream ss ( serial.substr ( 1 ) );

    {
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive

        iarchive ( items ); // Read the data from the archive
    }
}
