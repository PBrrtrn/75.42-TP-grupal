#ifndef _FOOD_H__
#define _FOOD_H__

#include "item.h"

class Food : public Item {

public:

	Food(Vector pos_inicial);

	bool pickUpAction(Player& p) override;

	~Food() override;

};

#endif



