#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H
#include "action.h"


class MoveRight : public Action {

    public:
        MoveRight(int clientID);
        void tryAction(Server &server) override;
        ~MoveRight();
};

#endif
