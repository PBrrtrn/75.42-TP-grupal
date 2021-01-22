#ifndef _BULLETS_H__
#define _BULLETS_H__

#include "item.h"

class Bullets : public Item {

public:

	Bullets(Vector pos_inicial);

	bool pickUpAction(Player& p) override;

	~Bullets() override;

};

#endif



