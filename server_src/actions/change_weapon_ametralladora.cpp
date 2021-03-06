#include "change_weapon_ametralladora.h"

ChangeWeaponAmetralladora::ChangeWeaponAmetralladora(){
	const YAML::Node& c = ServerConfig::Config["Ametralladora"];
    this->ametralladora_idx = c["Idx"].as<int>();
}

void ChangeWeaponAmetralladora::tryAction(GameStatus& gs, int clientID) {
	if (!gs.players.at(clientID).outGame()) {
		gs.players.at(clientID).changeWeapon(this->ametralladora_idx);	
	}
}

ChangeWeaponAmetralladora::~ChangeWeaponAmetralladora(){}
