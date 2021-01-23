#include "change_weapon_lanzacohetes.h"

ChangeWeaponLanzaCohetes::ChangeWeaponLanzaCohetes(){}

void ChangeWeaponLanzaCohetes::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(4);
	
}

ChangeWeaponLanzaCohetes::~ChangeWeaponLanzaCohetes(){}
