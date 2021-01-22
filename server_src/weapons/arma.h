#ifndef ARMA_H
#define ARMA_H

#include <string>

class Arma {
	protected:
		int precision;
		float cadencia; //cuanto dispara por segundo
		int balas;
		int attack_range;
		std::string nombre;

	public:
		Arma();
		Arma(std::string config);
		bool operator==(const Arma &another);
		bool is_empty();
		int getAttackRange();
		int getPrecision();
		virtual ~Arma();
};

#endif
