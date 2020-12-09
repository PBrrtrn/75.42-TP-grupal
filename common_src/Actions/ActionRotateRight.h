//
// Created by alejo on 30/11/20.
//

#ifndef TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATERIGHT_H
#define TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATERIGHT_H
#include "Action.h"
#include "../Server.h"

class ActionRotateRight : public Action {

public:
    ActionRotateRight(int clientID);
    void tryAction(Server &server) override;
    ~ActionRotateRight();
};


#endif //TP_FINAL_WOLFENSTEIN_3D_ACTIONROTATERIGHT_H
