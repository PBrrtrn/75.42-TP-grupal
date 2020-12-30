#ifndef SHOOT_H
#define SHOOT_H
#include "action.h"

class Shoot : public Action {

    public:
        Shoot();
        void tryAction(GameStatus& gs, int clientID, Map& map) override;
        ~Shoot();
};


#endif
