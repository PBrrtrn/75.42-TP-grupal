#ifndef _CHANGE_AMETRALLADORA__H_
#define _CHANGE_AMETRALLADORA__H_
#include "action.h"

class ChangeWeaponAmetralladora : public Action {

    public:
        ChangeWeaponAmetralladora();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponAmetralladora();
};

#endif
