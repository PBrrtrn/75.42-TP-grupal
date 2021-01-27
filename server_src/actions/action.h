#ifndef ACTION_H
#define ACTION_H

#include "../../common_src/Vector.h"
#include "../games/game_status.h"

class Action {
protected:
    int step;
    int rotation_left;
    int rotation_right;
    
public:
    explicit Action();
    virtual void tryAction(GameStatus& gs, int clientID);
    bool is_colision(int clientID, Vector& next_position, GameStatus& gs);
    ~Action();
};

#endif
