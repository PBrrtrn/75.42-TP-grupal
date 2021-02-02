#ifndef _CHANGE_CUCHILLO__H_
#define _CHANGE_CUCHILLO__H_
#include "action.h"

class ChangeWeaponCuchillo : public Action {
    private:
        int cuchillo_idx;
    public:
        ChangeWeaponCuchillo();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponCuchillo();
};

#endif
