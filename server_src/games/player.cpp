#include "player.h"

Player::Player(int id){
	this->id = id;	
	this->vidas = 3;
	this->health = 20;
	this->has_key = false;
	this->max_bullets = 100; //TODO definir bien y pasar a config
	this->bullets = 8; //TODO pasar a config -- cant balas con las que inicia
}

void Player::loseHealth(int amount) {
	this->health = this->health - amount;
	if (this->health <= 0 && this->vidas > 0) {
		this->health = 20;
		this->vidas--;
		this->has_key = false;
	}
}

int Player::getHealth() {
	return this->health;
}

bool Player::gainHealth(int amount) {
	if(this->health < 20) {
		this->health += amount;
		if(this->health > 20) this->health = 20;
		return true;
	}
	return false;
}

bool Player::addScore(int amount) {
	this->puntaje += amount;
	return true;
}

bool Player::addBullets(int amount) {
	if( this->bullets < this->max_bullets) {
		this->bullets += amount;
		if(this->bullets > this->max_bullets) this->bullets = this->max_bullets;
		return true;
	}
	return false;
}

bool Player::addWeapon(Arma& arma) {
	int free_idx;
	for(int i = 0; i < this->armas.size(); i++) {
		if (this->armas[i].is_empty()) free_idx = i;
		if (this->armas[i] == arma) {
			return false;
		}
	}
	this->armas[free_idx] = arma;
	return true;
}

bool Player::is_dead() {
	return this->vidas == 0;
}

bool Player::gainKey() {
	if(this->has_key) {
		return false;
	} else {
		this->has_key = true;
		return true;
	}
}

Player::~Player(){}
