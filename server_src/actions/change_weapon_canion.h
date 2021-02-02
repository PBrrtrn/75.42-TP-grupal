#ifndef _CHANGE_CANION__H_
#define _CHANGE_CANION__H_
#include "action.h"

class ChangeWeaponCanion : public Action {
    private:
        int canion_idx;

    public:
        ChangeWeaponCanion();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponCanion();
};

#endif
