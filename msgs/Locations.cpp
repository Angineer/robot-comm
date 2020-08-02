#include "Locations.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include <sstream>

Locations::Locations ( std::vector<std::string> locations ) :
    locations ( locations )
{
}

std::vector<std::string> Locations::get_locations(){
    return locations;
}

std::string Locations::get_serial() const{
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        // Write the data to the archive
        oarchive ( locations );
    }

    return "l" + ss.str();
}
