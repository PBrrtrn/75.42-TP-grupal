#include "change_weapon_ametralladora.h"

ChangeWeaponAmetralladora::ChangeWeaponAmetralladora(){}

void ChangeWeaponAmetralladora::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(2);
	
}

ChangeWeaponAmetralladora::~ChangeWeaponAmetralladora(){}
