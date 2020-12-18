#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H
#include "action.h"


class MoveRight : public Action {

    public:
        MoveRight();
        void tryAction(Server &server, int clientID) override;
        ~MoveRight();
};

#endif
