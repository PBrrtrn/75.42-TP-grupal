#ifndef MOVE_BACKWARD_H
#define MOVE_BACKWARD_H
#include "action.h"


class MoveBackward : public Action {

    public:
        MoveBackward(int clientID);
        void tryAction(Server &server) override;
        ~MoveBackward();
};

#endif
