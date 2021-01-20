#ifndef PLAYER_H
#define PLAYER_H

#define AMOUNT_WEAPONS 5

#include <array>
#include "../weapons/arma.h"

class Player {
	int id;
    int vida;
    std::array <Arma, AMOUNT_WEAPONS> armas;

public:
	
	Player(int id);
	~Player();
};

#endif //GAMESTATUS_H
