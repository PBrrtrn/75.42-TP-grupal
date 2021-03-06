#include "change_weapon_cuchillo.h"

ChangeWeaponCuchillo::ChangeWeaponCuchillo(){
	const YAML::Node& c = ServerConfig::Config["Cuchillo"];
    this->cuchillo_idx = c["Idx"].as<int>();
}

void ChangeWeaponCuchillo::tryAction(GameStatus& gs, int clientID) {
	if (!gs.players.at(clientID).outGame()) {
		gs.players.at(clientID).changeWeapon(this->cuchillo_idx);
	}
}

ChangeWeaponCuchillo::~ChangeWeaponCuchillo(){}
