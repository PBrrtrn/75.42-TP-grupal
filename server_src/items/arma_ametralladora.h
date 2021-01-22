#ifndef _ARMA_AMETRALLADORA_H__
#define _ARMA_AMETRALLADORA_H__

#include "item.h"
#include "../weapons/ametralladora.h"

class ArmaAmetralladora : public Item {
	private:
		Ametralladora ametralladora;

	public:
		ArmaAmetralladora(Vector pos_inicial);
		bool pickUpAction(Player& p) override;
		~ArmaAmetralladora() override;

};

#endif



