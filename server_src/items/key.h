#ifndef _KEY_H__
#define _KEY_H__

#include "item.h"

class Key : public Item {

public:

	Key(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Key() override;

};

#endif



