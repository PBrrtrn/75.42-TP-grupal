#ifndef PLAYER_H
#define PLAYER_H

#define AMOUNT_WEAPONS 5

#include <array>
#include "../weapons/arma.h"

class Player {
	int id;
    int vidas;
    int health;
    
    int puntaje;
    int max_bullets;
    int bullets;
    
    bool has_key;
    
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
	~Player();
};

#endif
