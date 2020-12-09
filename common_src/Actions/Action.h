//
// Created by alejo on 29/11/20.
//

#ifndef TP_FINAL_WOLFENSTEIN_3D_ACTION_H
#define TP_FINAL_WOLFENSTEIN_3D_ACTION_H

class Server;

class Action {
protected:
    int clientID;

public:
    explicit Action(int clientID);
    virtual void tryAction(Server &server) = 0;
    ~Action();
};


#endif //TP_FINAL_WOLFENSTEIN_3D_ACTION_H
