#ifndef SHOOT_H
#define SHOOT_H
#include "action.h"


class Shoot : public Action {

    public:
        Shoot(int clientID);
        void tryAction(Server &server) override;
        ~Shoot();
};


#endif
