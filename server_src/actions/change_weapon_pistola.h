#ifndef _CHANGE_PISTOLA__H_
#define _CHANGE_PISTOLA__H_
#include "action.h"

class ChangeWeaponPistola : public Action {
    private:
        int pistola_idx;
    public:
        ChangeWeaponPistola();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponPistola();
};

#endif
