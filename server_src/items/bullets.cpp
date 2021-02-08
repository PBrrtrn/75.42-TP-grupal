#include "bullets.h"

Bullets::Bullets(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 5;
    this->type = TYPE_BULLETS;
}

bool Bullets::pickUpAction(Player& p) {
    return p.addBullets(this->amount);
}

Bullets::~Bullets(){}
