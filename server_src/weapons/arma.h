#ifndef ARMA_H
#define ARMA_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "../server_config.h"

class Arma {
	protected:
		int precision;
		float cadencia; //cuanto dispara por segundo
		int balas;
		int attack_range;
		int indice;
		std::string nombre;

	public:
		Arma();
		bool operator==(const Arma &another);
		bool is_empty();
		int getAttackRange();
		int getIndex();
		virtual bool aimWeapon(float target_angle, float shooter_angle, float target_distance);
		float getCadencia();
		virtual ~Arma();
};

#endif
