#include "water.h"

Water::Water(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->canBePicked = false;
    this->isDecoration = true;
}

bool Water::pickUpAction(Player& p) {
    return false;
}

Water::~Water(){}
