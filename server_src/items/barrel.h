#ifndef _BARREL_H__
#define _BARREL_H__

#include "item.h"

class Barrel : public Item {

public:

	Barrel(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Barrel() override;

};

#endif

