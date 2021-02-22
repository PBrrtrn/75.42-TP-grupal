#ifndef _ARMA_LANZA_COHETES_H__
#define _ARMA_LANZA_COHETES_H__

#include "item.h"
#include "../weapons/lanzaCohetes.h"

class ArmaLanzaCohetes : public Item {

private:

	std::vector<LanzaCohetes*> lanza_cohetes;

public:

	ArmaLanzaCohetes(Vector pos_inicial,bool respawns);

	bool pickUpAction(Player& p) override;

	~ArmaLanzaCohetes() override;

};

#endif



