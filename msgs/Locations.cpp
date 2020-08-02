#include "Locations.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/map.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

const std::string Locations::type = "l";

Locations::Locations()
{
}

Locations::Locations ( const std::string& serial )
{
    deserialize ( serial );
}

void Locations::set_locations ( const std::map<int, std::string>& locations )
{
    this->locations = locations;
}

std::map<int, std::string> Locations::get_locations(){
    return locations;
}

std::string Locations::serialize() const{
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( locations );
    }

    return type + ss.str();
}

void Locations::deserialize ( const std::string& serial )
{
    // Read in new order
    std::stringstream ss ( serial.substr ( 1 ) );

    {
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive

        iarchive ( locations ); // Read the data from the archive
    }
}
