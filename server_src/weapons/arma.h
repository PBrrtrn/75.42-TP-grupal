#ifndef ARMA_H
#define ARMA_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "../server_config.h"

class Arma {
	protected:
		int precision;
		double cadencia; //cuanto dispara por segundo
		int balas;
		int attack_range;
		int indice;
		std::string nombre;

	public:
		Arma();
		bool operator==(const Arma &another);
		bool is_empty();
		int getAttackRange();
		int getPrecision();
		int getIndex();
		virtual ~Arma();
};

#endif
