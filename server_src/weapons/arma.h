#ifndef ARMA_H
#define ARMA_H

#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
#include "../server_config.h"

#define PI 3.14159265

class Arma {
	protected:
		float precision;
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
		void printNombre();
		virtual bool aimWeapon(float target_angle, float shooter_angle, float target_distance);
		float getCadencia();
		virtual ~Arma();
};

#endif
