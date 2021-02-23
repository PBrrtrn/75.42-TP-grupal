#include "action.h"
#include "shoot.h"
#include "../../common_src/RayCaster.h"

#include <iostream>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    //std::cout << "---------En tryAction de shoot----------" << std::endl;
    gs.changeFiringState(clientID, STATE_FIRING);
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

            /*
            std::cout << "target direction: x:" << target_direction.x << "y: " << target_direction.y << std::endl;
            std::cout << "target angle" << target_angle << std::endl;
            std::cout << "shooter angle" << shooter_angle << std::endl;
            std::cout << "shooter position: x:" << gs.getPosition(clientID).x << "y: " << gs.getPosition(clientID).y << std::endl;
            std::cout << "target position: x:" << gs.getPosition(target_id).x << "y: " << gs.getPosition(target_id).y << std::endl;
            std::cout << "wall distance: " << wall_distance << std::endl;
            std::cout << "target distance: " << target_distance << std::endl;
            */

            if (gs.players.at(clientID).aimWeapon(target_angle, shooter_angle, target_distance) && 
            target_distance < wall_distance) {
				//int danio = (int)(abs(rand()) / target_distance) % 10 + 1;
                int danio = 1+rand()%10;
                std::cout << "DANIO: " << danio << std::endl;
				if (target.loseHealth(danio) ) {
					std::cout << "player "<< target_id <<" has been killed, danio: "<< danio << std::endl;
					//TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
                    this->throwWeapon(gs.players.at(target_id).getSelectedWeaponIndex(), target_id, gs);
					gs.items.push_back(new Bullets(gs.getPosition(target_id),false));
                    gs.addEnemyDead(clientID);
				}
            }
            if (gs.players.at(clientID).loseBullet()) gs.addBulletShooted(clientID);
        }
    }
    //std::cout << "---------End tryAction de shoot----------" << std::endl;
}

void Shoot::throwWeapon(int weapon_idx, int target_id, GameStatus& gs) {
    Ametralladora a;
    CanionDeCadena c;
    LanzaCohetes lc;
    if (weapon_idx == a.getIndex()) {
        gs.items.push_back(new ArmaAmetralladora(gs.getPosition(target_id),false));
    } else if (weapon_idx == c.getIndex()) {
        gs.items.push_back(new ArmaCanion(gs.getPosition(target_id),false));
    } else if (weapon_idx == lc.getIndex()) {
        gs.items.push_back(new ArmaLanzaCohetes(gs.getPosition(target_id),false));
    }
}

Shoot::~Shoot() {}
