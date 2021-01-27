#include "change_weapon_ametralladora.h"

ChangeWeaponAmetralladora::ChangeWeaponAmetralladora(){
	const YAML::Node& c = ServerConfig::Config["Ametralladora"];
    this->ametralladora_idx = c["Idx"].as<int>();
}

void ChangeWeaponAmetralladora::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(this->ametralladora_idx);
	
}

ChangeWeaponAmetralladora::~ChangeWeaponAmetralladora(){}
