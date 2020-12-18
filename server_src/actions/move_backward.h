#ifndef MOVE_BACKWARD_H
#define MOVE_BACKWARD_H
#include "action.h"


class MoveBackward : public Action {

    public:
        MoveBackward();
        void tryAction(Server &server, int clientID) override;
        ~MoveBackward();
};

#endif
