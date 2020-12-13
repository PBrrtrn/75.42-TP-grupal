#ifndef MOVE_FORWARD_H
#define MOVE_FORWARD_H
#include "action.h"


class MoveForward : public Action {

    public:
        MoveForward(int clientID);
        void tryAction(Server &server) override;
        ~MoveForward();
};

#endif
