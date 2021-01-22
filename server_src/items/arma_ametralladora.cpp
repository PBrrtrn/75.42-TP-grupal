#include "arma_ametralladora.h"

ArmaAmetralladora::ArmaAmetralladora(Vector pos_inicial) : Item(pos_inicial), 
ametralladora("hola" /*TODO CONFIG*/) {}

bool ArmaAmetralladora::pickUpAction(Player& p) {
    return p.addWeapon(this->ametralladora);
}

ArmaAmetralladora::~ArmaAmetralladora(){}
