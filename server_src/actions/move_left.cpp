#include "action.h"
#include "move_left.h"

#include <iostream>

MoveLeft::MoveLeft() {}

void MoveLeft::tryAction(GameStatus& gs, int clientID){
  if (!gs.players.at(clientID).outGame()) {
    Vector pos = gs.getPosition(clientID);
		float angle = gs.getAngle(clientID);
    angle += this->rotation_left;
    gs.setAngle(clientID, angle);
  }
}

MoveLeft::~MoveLeft() {}
