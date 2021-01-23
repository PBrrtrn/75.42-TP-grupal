#include "medkit.h"

Medkit::Medkit(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 20; //TODO pasar a config
}

bool Medkit::pickUpAction(Player& p) {
    return p.gainHealth(this->amount);
}

Medkit::~Medkit(){}
