#include "player.h"

#include <iostream>

Player::Player(int id){
	const YAML::Node& c = ServerConfig::Config["Player"];
	
	this->id = id;	
	this->vidas = c["MaxLives"].as<int>();
	this->health = c["StartingHealth"].as<int>();
	this->has_key = false;
	this->puntaje = 0;
	this->max_bullets = c["MaxBullets"].as<int>();
	this->bullets = c["StartingBullets"].as<int>();
	this->armas[0] =  Cuchillo();
	this->armas[1] = Pistola();
	this->selected_weapon_idx = 1;
	this->movement_state = STATE_NOT_MOVING;
}

int Player::getWeaponPrecision() {
	return this->armas[this->selected_weapon_idx].getPrecision();
}

int Player::getWeaponAttackRange() {
	return this->armas[this->selected_weapon_idx].getAttackRange();
}

//si el jugador es muerto como resultado de perder vida, devuelvo true.
bool Player::loseHealth(int amount) {
	this->health = this->health - amount;
	if (this->health <= 0 && this->vidas > 0) {
		this->health = 20;
		this->vidas--;
		this->has_key = false;
		this->bullets = 8;
		this->puntaje = 0;
		this->selected_weapon_idx = 1;
		Arma a;
		this->armas[2] = a;
		this->armas[3] = a;
		this->armas[4] = a;
		this->movement_state = STATE_NOT_MOVING;
		return true;
	} else {
		return false;
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
	if (arma.getIndex() < this->armas.size() && this->armas[arma.getIndex()].is_empty()){
		return this->_addWeapon(arma.getIndex(),arma);
	}
	return false;
}

bool Player::_addWeapon(int idx, Arma& arma) {
	this->armas[idx] = arma;
	this->selected_weapon_idx = idx;
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

int Player::getPoints() {
	return this->puntaje;
}

int Player::getCurrentBullets(){
	return this->bullets;
}

bool Player::changeWeapon(int weapon_idx){
	if (this->armas[weapon_idx].is_empty()) return false;
	this->selected_weapon_idx = weapon_idx;
	return true;
}

int Player::getSelectedWeaponIndex(){
	return this->selected_weapon_idx;
}

bool Player::hasKey(){
	return this->has_key;
}

int Player::getLives(){
	return this->vidas;
}

bool Player::changeMovementState(MovementState state){
	this->movement_state = state;
	return true;
}

MovementState Player::getCurrentMovementState(){
	return this->movement_state;
}

bool Player::changeRotationState(MovementState state){
	this->rotation_state = state;
	return true;
}

MovementState Player::getCurrentRotationState(){
	return this->rotation_state;
}

Player::~Player(){}
