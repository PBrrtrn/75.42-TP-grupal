#ifndef _TABLE_H__
#define _TABLE_H__

#include "item.h"

class Table : public Item {

public:

	Table(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~Table() override;

};

#endif

