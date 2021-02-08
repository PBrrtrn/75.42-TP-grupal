#ifndef _ITEM_H__
#define _ITEM_H__

#include "../games/player.h"
#include "../../common_src/Vector.h"
#include "../../common_src/ItemType.h"

class Item {

protected:
	ItemType type;
	bool canBePicked;
	int timeToRespawn;
	int amount;
	Vector pos;
	bool respawns;
	bool isDecoration;
	bool has_volume;

public:

	//char item_type_id;

	Item(Vector pos_inicial,bool respawns);

	bool pickUp(Player& p);

	bool canBePickedUp();
	
	int getTimeToRespawn();
	
	/*Si el objeto fue creado como respawneable, reduce en 1 el timer. Si llego a 0 y es respawneable, se marca como levantable.*/
	bool tick();

	virtual bool pickUpAction(Player& p);

	Vector getPosition();
	
	bool isVisible();
	
	bool hasVolume();
	
	ItemType getType();

	virtual ~Item();
	
	friend class ItemSerializer;

};

#endif



