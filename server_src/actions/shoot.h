#ifndef SHOOT_H
#define SHOOT_H
#include "action.h"


class Shoot : public Action {

    public:
        Shoot();
        void tryAction(Server &server, int clientID) override;
        ~Shoot();
};


#endif
