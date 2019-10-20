#include "Order.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

Order::Order ( std::string location,
			   std::map<std::string, int> items ) :
	location ( location ),
	items ( items )
{
}

std::string Order::get_location(){
    return location;
}

std::map<std::string, int> Order::get_order(){
    return items;
}

void Order::write_serial(){
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( location, items );
    }

    serial = "o" + ss.str();
}
