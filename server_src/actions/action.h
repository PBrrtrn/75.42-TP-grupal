#ifndef ACTION_H
#define ACTION_H

class Server;

class Action {
    
public:
    explicit Action();
    virtual void tryAction(Server &server, int clientID);
    ~Action();
};

#endif
