#include "bullets.h"

Bullets::Bullets(Vector pos_inicial,bool respawns) : Item(pos_inicial,respawns) {
    this->amount = 5;
    this->type = TYPE_BULLETS;
}

bool Bullets::pickUpAction(Player& p) {
    //std::cout << "Player pickup BULLETS" << std::endl;
    return p.addBullets(this->amount);
}

Bullets::~Bullets(){}
