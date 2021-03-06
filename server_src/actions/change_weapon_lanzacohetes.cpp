#include "change_weapon_lanzacohetes.h"

ChangeWeaponLanzaCohetes::ChangeWeaponLanzaCohetes(){
	const YAML::Node& c = ServerConfig::Config["LanzaCohetes"];
    this->lanzacohetes_idx = c["Idx"].as<int>();
}

void ChangeWeaponLanzaCohetes::tryAction(GameStatus& gs, int clientID) {
	if (!gs.players.at(clientID).outGame()) {
		gs.players.at(clientID).changeWeapon(this->lanzacohetes_idx);
	}
}

ChangeWeaponLanzaCohetes::~ChangeWeaponLanzaCohetes(){}
