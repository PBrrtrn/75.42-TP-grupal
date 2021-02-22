#ifndef _FAKE_ITEM_H__
#define _FAKE_ITEM_H__

#include "item.h"

class FakeItem : public Item {

public:

	FakeItem(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~FakeItem() override;

};

#endif



