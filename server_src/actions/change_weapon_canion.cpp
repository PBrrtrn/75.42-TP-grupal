#include "change_weapon_canion.h"

ChangeWeaponCanion::ChangeWeaponCanion(){
	const YAML::Node& c = ServerConfig::Config["CanionDeCadena"];
    this->canion_idx = c["Idx"].as<int>();
}

void ChangeWeaponCanion::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(this->canion_idx);
	
}

ChangeWeaponCanion::~ChangeWeaponCanion(){}
