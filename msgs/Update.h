#ifndef UPDATE_H
#define UPDATE_H

#include "Message.h"
#include <string>

class Update: public Message
{
    public:
        Update();
        Update ( const std::string& serial );

        void set_update ( int slot_id, std::string new_type, int new_quant );
        std::tuple<int, std::string, int> get_update() const;

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        int slot_id;
        std::string new_type;
        int new_quant;
};

#endif
