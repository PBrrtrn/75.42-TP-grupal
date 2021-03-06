#include "action.h"
#include "move_forward.h"

#include <iostream>

MoveForward::MoveForward() {}

void MoveForward::tryAction(GameStatus& gs, int clientID){
    if (!gs.players.at(clientID).outGame()) {
        Vector pos = gs.getPosition(clientID);
        Vector direction = gs.getDirection(clientID);
        direction.turnUnitary();

        Vector next_position { pos.x + (direction.x * this->step),
                            pos.y - (direction.y * this->step) };

        is_colision(clientID, next_position, gs);
    }
}

MoveForward::~MoveForward() {}
