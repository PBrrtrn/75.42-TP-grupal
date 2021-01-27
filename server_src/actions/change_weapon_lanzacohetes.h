#ifndef _CHANGE_LANZA_COHETES__H_
#define _CHANGE_LANZA_COHETES__H_
#include "action.h"

class ChangeWeaponLanzaCohetes : public Action {
    private:
        int lanzacohetes_idx;
    public:
        ChangeWeaponLanzaCohetes();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponLanzaCohetes();
};

#endif
