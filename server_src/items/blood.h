#ifndef _BLOOD_H__
#define _BLOOD_H__

#include "item.h"

class Blood : public Item {

public:

	Blood(Vector pos_inicial);

	bool pickUpAction(Player& p) override;

	~Blood() override;

};

#endif



