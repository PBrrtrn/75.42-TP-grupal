#ifndef PLAYER_H
#define PLAYER_H

#define AMOUNT_WEAPONS 5

#include <array>
#include <yaml-cpp/yaml.h>
#include "../weapons/arma.h"
#include "../weapons/cuchillo.h"
#include "../weapons/ametralladora.h"
#include "../weapons/canionDeCadena.h"
#include "../weapons/lanzaCohetes.h"
#include "../weapons/pistola.h"
#include "../server_config.h"
#include "../actions/MovementState.h"


class Player {
	int id;
    int vidas;
    int health;
    
    int puntaje;
    int max_bullets;
    int bullets;
    
    bool has_key;
    int selected_weapon_idx;
    
    std::array<Arma,AMOUNT_WEAPONS> armas;
    MovementState movement_state;
    bool _addWeapon(int idx, Arma& arma);

public:
	
	Player(int id);
    bool loseHealth(int amount);
    bool gainHealth(int amount);
    int getHealth();
    bool is_dead();
    bool addScore(int amount);
    bool addBullets(int amount);
    bool gainKey();
    bool useKey();
    bool addWeapon(Arma& arma);
    int getWeaponPrecision();
    int getWeaponAttackRange();
    int getCurrentBullets();
    int getPoints();
    bool hasKey();
    int getLives();
    bool changeWeapon(int weapon_idx);
    int getSelectedWeaponIndex();
    bool changeMovementState(MovementState state);
    MovementState getCurrentMovementState();
	~Player();
};

#endif
