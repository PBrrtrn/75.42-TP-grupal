#ifndef _CHANGE_AMETRALLADORA__H_
#define _CHANGE_AMETRALLADORA__H_
#include "action.h"

class ChangeWeaponAmetralladora : public Action {
    private:
        int ametralladora_idx;

    public:
        ChangeWeaponAmetralladora();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponAmetralladora();
};

#endif
