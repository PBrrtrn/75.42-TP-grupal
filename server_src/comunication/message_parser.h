#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include "action.h"
#include <string>

class MessageParser {
    Action action;

    public:
        MessageParser();
        Action& parse(std::string message);
        ~MessageParser();
    
};

#endif