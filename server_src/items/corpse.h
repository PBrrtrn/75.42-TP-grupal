#ifndef _CORPSE_H__
#define _CORPSE_H__

#include "item.h"

class Corpse : public Item {

public:

	Corpse(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Corpse() override;

};

#endif
