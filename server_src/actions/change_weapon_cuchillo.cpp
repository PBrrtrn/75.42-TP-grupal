#include "change_weapon_cuchillo.h"

ChangeWeaponCuchillo::ChangeWeaponCuchillo(){}

void ChangeWeaponCuchillo::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(0);
	
}

ChangeWeaponCuchillo::~ChangeWeaponCuchillo(){}
