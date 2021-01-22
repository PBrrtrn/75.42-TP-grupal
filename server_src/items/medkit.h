#ifndef _MEDKIT_H__
#define _MEDKIT_H__

#include "item.h"

class Medkit : public Item {

public:

	Medkit(Vector pos_inicial);

	bool pickUpAction(Player& p) override;

	~Medkit() override;

};

#endif



