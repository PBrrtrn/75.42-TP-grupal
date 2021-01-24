#include "corpse.h"

Corpse::Corpse(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->canBePicked = false;
    this->isDecoration = true;
}

bool Corpse::pickUpAction(Player& p) {
    return false;
}

Corpse::~Corpse(){}
