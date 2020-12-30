#ifndef ACTION_H
#define ACTION_H

#include "../games/vector.h"
#include "../games/game_status.h"

// TODO pasar a configuration
#define STEP 5
#define ROTATION_LEFT 15
#define ROTATION_RIGHT -15

class Action {
    
public:
    explicit Action();
    virtual void tryAction(GameStatus& gs, int clientID, Map& map);
    bool is_colision(int clientID, Vector& next_position, Map& map, GameStatus& gs);
    ~Action();
};

#endif
