#include "blood.h"

Blood::Blood(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 1; //TODO pasar a config
}

bool Blood::pickUpAction(Player& p) {
    if (p.getHealth() < 11) {
        return p.gainHealth(this->amount);
    }
    return false;
}

Blood::~Blood(){}
