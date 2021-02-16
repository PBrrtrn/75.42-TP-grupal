#include "statistics.h"

Statistics::Statistics(){}

void Statistics::addEnemyDead(int playerID) {
    if (this->enemigos_matados.find(playerID) == this->enemigos_matados.end()) {
        this->enemigos_matados.insert({playerID, 1});
    } else {
        this->enemigos_matados.at(playerID) += 1;
    }
}

void Statistics::addPointsTreasure(int playerID, int amount) {
    if (this->puntos_tesoro.find(playerID) == this->puntos_tesoro.end()) {
        this->puntos_tesoro.insert({playerID, amount});
    } else {
        this->puntos_tesoro.at(playerID) = amount;
    }
}

void Statistics::addBulletShooted(int playerID) {
    if (this->balas_disparadas.find(playerID) == this->balas_disparadas.end()) {
        this->balas_disparadas.insert({playerID, 1});
    } else {
        this->balas_disparadas.at(playerID) += 1;
    }
}

Statistics::~Statistics() {}
