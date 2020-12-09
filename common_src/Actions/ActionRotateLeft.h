//
// Created by alejo on 30/11/20.
//

#ifndef TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATELEFT_H
#define TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATELEFT_H
#include "Action.h"
#include "../Server.h"

class ActionRotateLeft : public Action {

public:
    ActionRotateLeft(int clientID);
    void tryAction(Server &server) override;
    ~ActionRotateLeft();
};


#endif //TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATELEFT_H
