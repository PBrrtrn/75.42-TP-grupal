#include "statistics.h"

Statistics::Statistics(){}

void Statistics::addEnemyDead(int playerID) {
    this->enemigos_matados.at(playerID) += 1;
}

void Statistics::addPointsTreasure(int playerID, int amount) {
    this->puntos_tesoro.at(playerID) = amount;
}

void Statistics::addBulletShooted(int playerID) {
    this->balas_disparadas.at(playerID) += 1;
}

Statistics::~Statistics() {}
