#include "Inventory.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

Inventory::Inventory ( std::map<std::string, int> items ) :
    items ( items )
{
}

std::map<std::string, int> Inventory::get_items(){
    return items;
}

std::string Inventory::get_serial() const{
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( items );
    }

    return "i" + ss.str();
}
