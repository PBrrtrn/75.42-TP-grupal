#ifndef PLAYER_H
#define PLAYER_H

#define AMOUNT_WEAPONS 5

#include <array>
#include "../weapons/arma.h"
#include "../weapons/cuchillo.h"
#include "../weapons/ametralladora.h"
#include "../weapons/canionDeCadena.h"
#include "../weapons/lanzaCohetes.h"
#include "../weapons/pistola.h"

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

public:
	
	Player(int id);
    void loseHealth(int amount);
    bool gainHealth(int amount);
    int getHealth();
    bool is_dead();
    bool addScore(int amount);
    bool addBullets(int amount);
    bool gainKey();
    bool addWeapon(Arma& arma);
    int getWeaponPrecision();
    int getWeaponAttackRange();
	~Player();
};

#endif
