#include "change_weapon_canion.h"

ChangeWeaponCanion::ChangeWeaponCanion(){}

void ChangeWeaponCanion::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(3);
	
}

ChangeWeaponCanion::~ChangeWeaponCanion(){}
