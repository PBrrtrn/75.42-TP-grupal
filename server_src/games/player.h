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
    
    bool has_key;
    
    std::array<Arma,AMOUNT_WEAPONS> armas;

public:
	
	Player(int id);
    void loseHealth(int amount);
    bool is_dead();
	~Player();
};

#endif
