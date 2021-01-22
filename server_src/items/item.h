#ifndef _ITEM_H__
#define _ITEM_H__

#include "../games/player.h"
#include "../games/vector.h"

class Item {

private:
	bool canBePicked;
	int timeToRespawn;
	int amount;
	Vector pos;

public:

	Item(Vector pos_inicial);

	bool pickUp(Player& p);

	bool canBePickedUp();

	Vector getPosition();

	virtual ~Item();

};

#endif



