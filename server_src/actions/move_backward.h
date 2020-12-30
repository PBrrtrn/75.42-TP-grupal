#ifndef MOVE_BACKWARD_H
#define MOVE_BACKWARD_H
#include "action.h"

class MoveBackward : public Action {

    public:
        MoveBackward();
        void tryAction(GameStatus& gs, int clientID, Map& map) override;
        ~MoveBackward();
};

#endif
