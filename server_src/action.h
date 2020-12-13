#ifndef ACTION_H
#define ACTION_H

class Server;

class Action {
protected:
    int clientID;

public:
    explicit Action(int clientID);
    virtual void tryAction(Server &server);
    ~Action();
};

#endif
