#include "arma_ametralladora.h"

ArmaAmetralladora::ArmaAmetralladora(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
ametralladora() {}

bool ArmaAmetralladora::pickUpAction(Player& p) {
    return p.addWeapon(this->ametralladora);
}

ArmaAmetralladora::~ArmaAmetralladora(){}
