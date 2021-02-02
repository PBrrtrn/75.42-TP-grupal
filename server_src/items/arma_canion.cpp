#include "arma_canion.h"

ArmaCanion::ArmaCanion(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
canion() {}

bool ArmaCanion::pickUpAction(Player& p) {
    return p.addWeapon(this->canion);
}

ArmaCanion::~ArmaCanion(){}
