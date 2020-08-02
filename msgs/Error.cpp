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

Error::Error(ErrorCode code){
    this->code = code;
}

std::string Error::get_serial() const {
    return "s" + std::to_string(int(code));
}
