#ifndef UPDATE_H
#define UPDATE_H

#include "Message.h"
#include <string>

class Update: public Message
{
    private:
        int slot_id;
        std::string new_type;
        int new_quant;
    public:
        Update(int slot_id, std::string new_type, int new_quant);
        void write_serial();
};

#endif
