#ifndef SHOOT_H
#define SHOOT_H
#include "action.h"

#define DELTA 0.1

class Shoot : public Action {

    public:
        Shoot();
        void tryAction(GameStatus& gs, int clientID) override;
        ~Shoot();
};


#endif
