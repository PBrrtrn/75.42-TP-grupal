#ifndef MOVE_RIGHT_H
#define MOVE_RIGHT_H
#include "action.h"


class MoveRight : public Action {

    public:
        MoveRight();
        void tryAction(GameStatus& gs, int clientID) override;
        ~MoveRight();
};

#endif
