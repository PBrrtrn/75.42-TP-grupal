#include "change_weapon_pistola.h"

ChangeWeaponPistola::ChangeWeaponPistola(){
	const YAML::Node& c = ServerConfig::Config["Pistola"];
    this->pistola_idx = c["Idx"].as<int>();
}

void ChangeWeaponPistola::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(this->pistola_idx);
	
}

ChangeWeaponPistola::~ChangeWeaponPistola(){}
