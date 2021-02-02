#include "action.h"
#include "shoot.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    for (auto& it: gs.players) {
        int target_id = it.first;
        Player& target = it.second;
        if (target_id != clientID && !target.is_dead()) {
            float shooter_direction = gs.getAngle(clientID);
            Vector target_direction = gs.getPosition(target_id) - gs.getPosition(clientID);
            float target_angle = target_direction.getAngle();
            float target_distance = target_direction.norm();

            if (target_angle < shooter_direction + DELTA && 
                 target_angle > shooter_direction - DELTA && 
                 target_distance <= gs.players.at(clientID).getWeaponAttackRange()) {
				int precision = gs.players.at(clientID).getWeaponPrecision();
				int danio = (rand() % 10 + 1) * precision / target_distance;
				if (target.loseHealth(danio) ) {
					std::cout << "this player has been killed" << std::endl;
					//TODO: El arma a dropear tiene que ser del tipo que llevaba el jugador muerto en ese momento.
					//TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
					gs.items.push_back(ArmaAmetralladora(gs.getPosition(target_id),false));
					gs.items.push_back(Bullets(gs.getPosition(target_id),false));
                    gs.addEnemyDead(clientID);
				}
            }
        }
    }
    gs.addBulletShooted(clientID);
}

Shoot::~Shoot() {}
