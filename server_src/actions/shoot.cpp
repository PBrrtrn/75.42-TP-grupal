#include "action.h"
#include "shoot.h"
#include "../../common_src/RayCaster.h"

#include <iostream>
#include <cmath>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    gs.changeFiringState(clientID, STATE_FIRING);
    for (auto& it: gs.players) {
        int target_id = it.first;
        Player& target = it.second;
        if (target_id != clientID && !target.is_dead()) {
            Vector player_pos = gs.getPosition(clientID);
            Vector target_pos = gs.getPosition(target_id);

            Vector player_dir(gs.getAngle(clientID));
            Vector target_dir = target_pos - player_pos;

            float angle = abs(player_dir.getAngle()) - abs(target_dir.getAngle());
            if (abs(angle) < M_PI/2) {
                float scalar = player_dir.x * target_dir.x;
                scalar += player_dir.y * target_dir.y;
                scalar = scalar / pow(player_dir.norm(), 2);

                Vector projection { scalar * player_dir.x, 
                                    - scalar * player_dir.y };
                float ort_dist = (target_dir - projection).norm();
                float target_dist = target_dir.norm();

                RayCaster ray_caster;
                RayHit hit = ray_caster.castRay(gs.getMap(), target_pos, target_dir.getAngle());
                float wall_distance = hit.distance;

                bool hit_wall = wall_distance < target_dist;
                bool hit_enemy = gs.players.at(clientID).aimWeapon(ort_dist, target_dist);
                if (hit_enemy && !hit_wall) {
                    int danio = 1+rand()%10;
                    if (target.loseHealth(danio) ) {
                        std::cout << "Player "<< target_id <<" has been killed" << std::endl;
                        //TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
                        this->throwWeapon(gs.players.at(target_id).getSelectedWeaponIndex(), target_id, gs);
                        gs.items.push_back(new Bullets(gs.getPosition(target_id),false));
                        gs.addEnemyDead(clientID);
                    }
                }
            }

            /*
            float shooter_angle = gs.getAngle(clientID);
            Vector target_direction = gs.getPosition(target_id) - gs.getPosition(clientID);
            float target_angle = target_direction.getAngle();
            float target_distance = target_direction.norm();

            RayCaster ray_caster;
            float wall_distance = abs(ray_caster.castRay(gs.getMap(), gs.getPosition(target_id), target_angle).distance);

            if (gs.players.at(clientID).aimWeapon(target_angle, shooter_angle, target_distance) && 
            target_distance < wall_distance) {
				//int danio = (int)(abs(rand()) / target_distance) % 10 + 1;
                int danio = 1+rand()%10;
				if (target.loseHealth(danio) ) {
					std::cout << "Player "<< target_id <<" has been killed" << std::endl;
					//TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
                    this->throwWeapon(gs.players.at(target_id).getSelectedWeaponIndex(), target_id, gs);
					gs.items.push_back(new Bullets(gs.getPosition(target_id),false));
                    gs.addEnemyDead(clientID);
				}
            }
            */
            if (gs.players.at(clientID).loseBullet()) gs.addBulletShooted(clientID);
        }
    }
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
