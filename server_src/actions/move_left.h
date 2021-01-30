#ifndef MOVE_LEFT_H
#define MOVE_LEFT_H
#include "action.h"


class MoveLeft : public Action {
    public:
        MoveLeft();
        void tryAction(GameStatus& gs, int clientID) override;
        ~MoveLeft();
};

#endif
