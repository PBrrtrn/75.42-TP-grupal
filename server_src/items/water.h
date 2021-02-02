#ifndef _WATER_H__
#define _WATER_H__

#include "item.h"

class Water : public Item {

public:

	Water(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Water() override;

};

#endif

