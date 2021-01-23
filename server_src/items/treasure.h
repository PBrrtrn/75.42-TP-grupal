#ifndef _TREASURE_H__
#define _TREASURE_H__

#include "item.h"

class Treasure : public Item {

public:

	Treasure(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Treasure() override;

};

#endif



