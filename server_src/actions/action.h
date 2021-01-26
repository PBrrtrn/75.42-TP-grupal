#ifndef ACTION_H
#define ACTION_H

#include "../../common_src/Vector.h"
#include "../games/game_status.h"

// TODO pasar a configuration
#define STEP 5
#define ROTATION_LEFT 15
#define ROTATION_RIGHT -15

class Action {
    
public:
    explicit Action();
    virtual void tryAction(GameStatus& gs, int clientID);
    bool is_colision(int clientID, Vector& next_position, GameStatus& gs);
    ~Action();
};

#endif
