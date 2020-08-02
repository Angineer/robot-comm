#include "Error.h"

ErrorCode string_to_status(std::string input){
    if(input == "battery_low") return ErrorCode::BATTERY_LOW;

    return ErrorCode::UNKNOWN;
}

std::string status_to_string(ErrorCode input){
    switch(input){
        case ErrorCode::BATTERY_LOW: return "battery_low";

        default: return "unknown";
    }
}

const std::string Error::type = "e";

Error::Error ( const std::string& serial )
{
    deserialize ( serial );
}

std::string Error::serialize() const {
    return type + std::to_string ( int ( code ) );
}

void Error::deserialize ( const std::string& serial )
{
    code = static_cast<ErrorCode> ( stoi ( serial.substr ( 1 ) ) );
}
