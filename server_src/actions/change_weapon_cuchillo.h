#ifndef _CHANGE_CUCHILLO__H_
#define _CHANGE_CUCHILLO__H_
#include "action.h"

class ChangeWeaponCuchillo : public Action {

    public:
        ChangeWeaponCuchillo();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponCuchillo();
};

#endif
