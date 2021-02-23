#ifndef SHOOT_H
#define SHOOT_H
#include "action.h"
#include "../items/arma_ametralladora.h"
#include "../items/bullets.h"

class Shoot : public Action {
    public:
        Shoot();
        void throwWeapon(int weapon_idx, int target_id, GameStatus& gs);
        void tryAction(GameStatus& gs, int clientID) override;
        ~Shoot();
};

#endif
