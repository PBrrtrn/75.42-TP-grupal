#ifndef ARMA_H
#define ARMA_H

#include <string>

class Arma {
	protected:
		int precision;
		float cadencia; //cuanto dispara por segundo
		std::string nombre;

	public:
		Arma(std::string config);
		virtual ~Arma();
};

#endif //GAMESTATUS_H
