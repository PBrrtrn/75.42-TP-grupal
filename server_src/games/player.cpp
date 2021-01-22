#include "player.h"

Player::Player(int id){
	this->id = id;	
	this->vidas = 3;
	this->health = 20;
	this->has_key = false;
}

void Player::loseHealth(int amount) {
	this->health = this->health - amount;
	if (this->health <= 0 && this->vidas > 0) {
		this->health = 20;
		this->vidas--;
		this->has_key = false;
	}
}

bool Player::is_dead() {
	return this->vidas == 0;
}

Player::~Player(){}
