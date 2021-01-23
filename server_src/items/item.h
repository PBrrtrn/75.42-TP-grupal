#ifndef _ITEM_H__
#define _ITEM_H__

#include "../games/player.h"
#include "../games/vector.h"

class Item {

protected:
	bool canBePicked;
	int timeToRespawn;
	int amount;
	Vector pos;
	bool respawns;

public:

	Item(Vector pos_inicial,bool respawns);

	bool pickUp(Player& p);

	bool canBePickedUp();
	
	int getTimeToRespawn();
	
	/*Si el objeto fue creado como respawneable, reduce en 1 el timer. Si llego a 0 y es respawneable, se marca como levantable.*/
	bool tick();

	virtual bool pickUpAction(Player& p);

	Vector getPosition();

	virtual ~Item();

};

#endif



