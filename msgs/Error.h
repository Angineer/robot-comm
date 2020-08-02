#ifndef ERROR_H
#define ERROR_H

#include <string>

#include "Message.h"

enum class ErrorCode
{
    UNKNOWN = 0,
    BATTERY_LOW = 1
};

ErrorCode string_to_code ( std::string input );
std::string code_to_string ( ErrorCode input );

class Error: public Message {
    public:
        Error();
        Error ( const std::string& serial );

        void set_code ( ErrorCode code );
        std::string get_code();

        std::string serialize() const override;
        void deserialize ( const std::string& serial ) override;

    private:
        static const std::string type;
        ErrorCode code;
};

#endif
