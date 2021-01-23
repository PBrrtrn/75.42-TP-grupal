#include "change_weapon_pistola.h"

ChangeWeaponPistola::ChangeWeaponPistola(){}

void ChangeWeaponPistola::tryAction(GameStatus& gs, int clientID) {
	gs.players.at(clientID).changeWeapon(1);
	
}

ChangeWeaponPistola::~ChangeWeaponPistola(){}
