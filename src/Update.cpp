#include "Update.h"

#include "cereal/cereal.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/string.hpp"
#include <sstream>

Update::Update(int slot_id, std::string new_type, int new_quant){
    this->slot_id = slot_id;
    this->new_type = new_type;
    this->new_quant = new_quant;
}

void Update::write_serial(){
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive oarchive(ss); // Create an output archive

        oarchive(slot_id, new_type, new_quant); // Write the data to the archive
    }

    serial = "u" + ss.str();
}
