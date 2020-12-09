#ifndef TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEFORWARD_H
#define TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEFORWARD_H
#include "Action.h"


class ActionMoveForward : public Action {

public:
    ActionMoveForward(int clientID);
    void tryAction(Server &server) override;
    ~ActionMoveForward();
};


#endif //TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEMENT_H
