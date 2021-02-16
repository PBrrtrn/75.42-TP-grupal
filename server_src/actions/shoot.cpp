#include "action.h"
#include "shoot.h"
#include "../../common_src/RayCaster.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    std::cout << "---------En tryAction de shoot----------" << std::endl;
    for (auto& it: gs.players) {
        int target_id = it.first;
        Player& target = it.second;
        if (target_id != clientID && !target.is_dead()) {
            float shooter_angle = gs.getAngle(clientID);
            Vector target_direction = gs.getPosition(target_id) - gs.getPosition(clientID);
            float target_angle = target_direction.getAngle();
            float target_distance = target_direction.norm();

            RayCaster ray_caster;
            float wall_distance = abs(ray_caster.castRay(gs.getMap(), gs.getPosition(target_id), target_angle).distance);

            if (gs.players.at(clientID).aimWeapon(target_angle, shooter_angle, target_distance) && 
            target_distance < wall_distance) {
				int danio = (int)(abs(rand()) / target_distance) % 10 + 1;
				if (target.loseHealth(danio) ) {
					std::cout << "player "<< target_id <<" has been killed, danio: "<< danio << std::endl;
					//TODO: El arma a dropear tiene que ser del tipo que llevaba el jugador muerto en ese momento.
					//TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
					gs.items.push_back(ArmaAmetralladora(gs.getPosition(target_id),false));
					gs.items.push_back(Bullets(gs.getPosition(target_id),false));
                    gs.addEnemyDead(clientID);
				}
            }
        }
    }
    gs.players.at(clientID).loseBullet();
    gs.addBulletShooted(clientID);
    std::cout << "---------End tryAction de shoot----------" << std::endl;
}

Shoot::~Shoot() {}
