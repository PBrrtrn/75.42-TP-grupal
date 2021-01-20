#include "action.h"
#include "shoot.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    for (auto& it: gs.players) {
        int target_id = it.first;
        if (target_id != clientID) {
            float shooter_direction = gs.getAngle(clientID);
            float target_direction = (gs.getPosition(target_id) - gs.getPosition(clientID)).getAngle();

            if (target_direction < shooter_direction + DELTA && 
                target_direction > shooter_direction - DELTA) {
                    int danio = rand() % 10 + 1; //danio random entre 1 a 10
                    gs.players.at(target_id).loseHealth(danio);
                    //TODO manejar mas danio con distancia mas chica
                    /*
                    if (gs.players.at(target_id).is_dead()) {
                        gs.players.erase(target_id);
                    }*/
            }
        }
    }
}

Shoot::~Shoot() {}
