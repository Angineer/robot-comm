#include "Update.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

const std::string Update::type = "u";

Update::Update()
{
}

Update::Update ( const std::string& serial )
{
    deserialize ( serial );
}

void Update::set_update ( int slot_id, std::string new_type, int new_quant )
{
    this->slot_id = slot_id;
    this->new_type = new_type;
    this->new_quant = new_quant;
}
std::tuple<int, std::string, int> Update::get_update() const
{
    return std::make_tuple ( slot_id, new_type, new_quant );
}

std::string Update::serialize() const {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        oarchive(slot_id, new_type, new_quant); // Write the data to the archive
    }

    return type + ss.str();
}

void Update::deserialize ( const std::string& serial )
{
    std::stringstream ss ( serial.substr ( 1 ) );

    {
        cereal::BinaryInputArchive iarchive(ss); // Create an input archive

        iarchive ( slot_id, new_type, new_quant ); // Read the data from the archive
    }
}
