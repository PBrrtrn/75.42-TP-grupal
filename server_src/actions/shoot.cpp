#include "action.h"
#include "shoot.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    for (auto& it: gs.players) {
        int target_id = it.first;
        if (target_id != clientID) {
            float shooter_direction = gs.getAngle(clientID);
            Vector target_direction = gs.getPosition(target_id) - gs.getPosition(clientID);
            float target_angle = target_direction.getAngle();
            float target_distance = target_direction.calculateNorma();

            if (target_angle < shooter_direction + DELTA && 
                target_angle > shooter_direction - DELTA && 
                target_distance <= gs.players.at(clientID).getWeaponAttackRange()) {
                    int precision = gs.players.at(clientID).getWeaponPrecision();
                    int danio = (rand() % 10 + 1) * precision / target_distance;
                    gs.players.at(target_id).loseHealth(danio);
            }
        }
    }
}

Shoot::~Shoot() {}
