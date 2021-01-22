#ifndef ARMA_H
#define ARMA_H

#include <string>

class Arma {
	protected:
		int precision;
		float cadencia; //cuanto dispara por segundo
		int balas;
		std::string nombre;

	public:
		Arma();
		Arma(std::string config);
		virtual ~Arma();
};

#endif
