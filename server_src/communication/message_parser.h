#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include "../actions/action.h"
#include <string>

class MessageParser {
    Action action;

    public:
        MessageParser();
        Action& parse(std::string message);
        ~MessageParser();
    
};

#endif