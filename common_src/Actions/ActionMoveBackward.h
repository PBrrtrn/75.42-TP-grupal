//
// Created by alejo on 30/11/20.
//

#ifndef TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEBACKWARD_H
#define TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEBACKWARD_H
#include "Action.h"
#include "../Server.h"

class ActionMoveBackward : public Action{

public:
    ActionMoveBackward(int clientID);
    void tryAction(Server &server) override;
    ~ActionMoveBackward();
};


#endif //TP_FINAL_WOLFENSTEIN_3D_ACTIONMOVEBACKWARD_H
