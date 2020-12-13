#ifndef MOVE_LEFT_H
#define MOVE_LEFT_H
#include "action.h"


class MoveLeft : public Action {

    public:
        MoveLeft(int clientID);
        void tryAction(Server &server) override;
        ~MoveLeft();
};

#endif
