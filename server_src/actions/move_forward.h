#ifndef MOVE_FORWARD_H
#define MOVE_FORWARD_H
#include "action.h"

class MoveForward : public Action {
    public:
        MoveForward();
        void tryAction(GameStatus& gs, int clientID) override;
        ~MoveForward();
};

#endif
