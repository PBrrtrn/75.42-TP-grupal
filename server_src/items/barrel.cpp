#include "barrel.h"

Barrel::Barrel(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->canBePicked = false;
    this->isDecoration = true;
    this->has_volume = true;
}

bool Barrel::pickUpAction(Player& p) {
    return false;
}

Barrel::~Barrel(){}
