#include "Order.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

Order::Order ( std::map<std::string, int> items ){
    this->items = items;
}

std::map<std::string, int> Order::get_order(){
    return this->items;
}

void Order::write_serial(){
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        oarchive(this->items); // Write the data to the archive
    }

    serial = "o" + ss.str();
}
