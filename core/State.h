#ifndef STATE_H
#define STATE_H

enum class State
{
    IDLE,
    DISPENSE,
    DELIVER,
    RETURN,
    ERROR
};

inline std::string stateToString ( State state ) {
    if ( state == State::IDLE ) {
        return "IDLE";
    } else if ( state == State::DISPENSE ) {
        return "DISPENSE";
    } else if ( state == State::DELIVER ) {
        return "DELIVER";
    } else if ( state == State::RETURN ) {
        return "RETURN";
    } else {
        return "ERROR";
    }
}

inline State stringToState ( std::string string ) {
    if ( string == "IDLE" ) {
        return State::IDLE;
    } else if ( string == "DISPENSE" ) {
        return State::DISPENSE;
    } else if ( string == "DELIVER" ) {
        return State::DELIVER;
    } else if ( string == "RETURN" ) {
        return State::RETURN;
    } else {
        return State::ERROR;
    }
}

#endif
