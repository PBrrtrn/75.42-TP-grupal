#ifndef _USE_DOOR__H_
#define _USE_DOOR__H_
#include "action.h"

class UseDoor : public Action {

    public:
        UseDoor();
        void tryAction(GameStatus& gs, int clientID) override;
        ~UseDoor();
};

#endif
