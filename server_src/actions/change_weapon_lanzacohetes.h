#ifndef _CHANGE_LANZA_COHETES__H_
#define _CHANGE_LANZA_COHETES__H_
#include "action.h"

class ChangeWeaponLanzaCohetes : public Action {

    public:
        ChangeWeaponLanzaCohetes();
        void tryAction(GameStatus& gs, int clientID) override;
        ~ChangeWeaponLanzaCohetes();
};

#endif
