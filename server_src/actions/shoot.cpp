#include "action.h"
#include "shoot.h"
#include "../../common_src/RayCaster.h"

#include <iostream>
#include <cmath>

Shoot::Shoot(){}

void Shoot::tryAction(GameStatus& gs, int clientID){
    if (gs.players.at(clientID).loseBullet()) gs.addBulletShooted(clientID);
    gs.changeFiringState(clientID, STATE_FIRING);

    Vector position = gs.getPosition(clientID);
    float angle = gs.getAngle(clientID);

    int map_column = int(position.x);
    int map_row = int(position.y);

    float dir_x = cos(angle);
    float dir_y = sin(angle);

    float columnwise_delta = std::abs(1/dir_x);
    float rowwise_delta = std::abs(1/dir_y);

    float first_column_distance;
    int columnwise_step;
    if (dir_x > 0) {
        columnwise_step = 1;
        first_column_distance = 1 - (position.x - map_column);
    } else {
        columnwise_step = -1;
        first_column_distance = (position.x - map_column);
    }

    float first_row_distance;
    int rowwise_step;
    if (dir_y > 0) {
        rowwise_step = -1;
        first_row_distance = (position.y - map_row);
    } else {
        rowwise_step = 1;
        first_row_distance = 1 - (position.y - map_row);
    }

    float columnwise_distance = first_column_distance * columnwise_delta;
    float rowwise_distance = first_row_distance * rowwise_delta;

    int hit_side = 1;
    while (gs.getMap()[map_row][map_column] < 1) {
        for (auto& it: gs.players) {
            int target_id = it.first;
            Player& target = it.second;
            if (target_id != clientID && !target.is_dead()) {
                Vector tgt = gs.getPosition(target_id);
                float x_distance = float(tgt.x - float(map_column));
                float y_distance = float(tgt.y - float(map_row));
                float ort_dist = fabs(x_distance) + fabs(y_distance);

                float target_dist = fabs((tgt - position).norm());

                if (gs.players.at(clientID).aimWeapon(ort_dist, target_dist)) {
                    int danio = 1+rand()%10;
                    if (target.loseHealth(danio) ) {
                        std::cout << "Player "<< target_id <<" has been killed" << std::endl;
                        //TODO: Dropear item falso "cadaver" que no va a ser utilizable pero si visible.
                        this->throwWeapon(gs.players.at(target_id).getSelectedWeaponIndex(), target_id, gs);
                        gs.items.push_back(new Bullets(gs.getPosition(target_id),false));
                        gs.addEnemyDead(clientID);
                        std::vector<SpawnPoint> spawnpoints = gs.getSpawnPoints();
                        int sp_idx = rand()% (spawnpoints.size());
                        Vector position = spawnpoints[sp_idx].getPosition();
                        gs.setPosition(target_id, position);
                    }
                    return;
                }
            }
        }

        if (columnwise_distance < rowwise_distance) {
            map_column += columnwise_step;
            columnwise_distance += columnwise_delta;
            hit_side = 0;
        } else {
            map_row += rowwise_step;
            rowwise_distance += rowwise_delta;
            hit_side = 1;
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
