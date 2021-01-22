#ifndef _ARMA_CANION_H__
#define _ARMA_CANION_H__

#include "item.h"
#include "../weapons/canionDeCadena.h"

class ArmaCanion : public Item {

private:

	CanionDeCadena canion;

public:

	ArmaCanion(Vector pos_inicial);

	bool pickUpAction(Player& p) override;

	~ArmaCanion() override;

};

#endif



