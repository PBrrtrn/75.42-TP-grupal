#include "arma_lanzacohetes.h"

ArmaLanzaCohetes::ArmaLanzaCohetes(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns), 
lanza_cohetes("hola" /*TODO CONFIG*/) {}

bool ArmaLanzaCohetes::pickUpAction(Player& p) {
    return p.addWeapon(this->lanza_cohetes);
}

ArmaLanzaCohetes::~ArmaLanzaCohetes(){}
