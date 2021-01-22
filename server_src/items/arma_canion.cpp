#include "arma_canion.h"

ArmaCanion::ArmaCanion(Vector pos_inicial) : Item(pos_inicial), 
canion("hola" /*TODO CONFIG*/) {}

bool ArmaCanion::pickUpAction(Player& p) {
    return p.addWeapon(this->canion);
}

ArmaCanion::~ArmaCanion(){}
