#include "player.h"

Player::Player(int id){
	this->id = id;	
	this->vidas = 3;
	this->health = 20;
	this->has_key = false;
	this->max_bullets = 100; //TODO definir bien y pasar a config
	this->bullets = 8; //TODO pasar a config -- cant balas con las que inicia
	this->armas[0] =  Cuchillo("config");
	this->armas[1] = Pistola("config");
	this->selected_weapon_idx = 1;
}

int Player::getWeaponPrecision() {
	return this->armas[this->selected_weapon_idx].getPrecision();
}

int Player::getWeaponAttackRange() {
	return this->armas[this->selected_weapon_idx].getAttackRange();
}

void Player::loseHealth(int amount) {
	this->health = this->health - amount;
	if (this->health <= 0 && this->vidas > 0) {
		this->health = 20;
		this->vidas--;
		this->has_key = false;
		this->bullets = 8;
		this->selected_weapon_idx = 1;
		Arma a("config");
		this->armas[2] = a;
		this->armas[3] = a;
		this->armas[4] = a;
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
	this->selected_weapon_idx = free_idx;
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

bool Player::useKey(){
	if (this->has_key){
		this->has_key = false;
		return true;
	} else {
		return false;
	}
}

int Player::getCurrentBullets(){
	return this->bullets;
}

bool Player::changeWeapon(int weapon_idx){
	this->selected_weapon_idx = weapon_idx;
	return true;
}

Player::~Player(){}
