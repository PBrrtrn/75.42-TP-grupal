#include "player.h"

#include <iostream>

Player::Player(int id) : 
	receivedDamage(false),
	died(false),
	pickedUpTreasure(false),
	pickedUpBullets(false),
	pickedUpLife(false),
	before_respawn(false)
	{
	const YAML::Node& c = ServerConfig::Config["Player"];
	
	this->id = id;	
	this->vidas = c["MaxLives"].as<int>();
	this->health = c["StartingHealth"].as<int>();
	this->has_key = false;
	this->puntaje = 0;
	this->max_bullets = c["MaxBullets"].as<int>();
	this->bullets = c["StartingBullets"].as<int>();
	this->armas[0] =  new Cuchillo();
	this->armas[1] = new Pistola();
	this->armas[2] = NULL; //new Ametralladora();//
	this->armas[3] = NULL; //new CanionDeCadena();//
	this->armas[4] = NULL;
	this->selected_weapon_idx = 1;
	this->previous_weapon_idx = 0;
	this->movement_state = STATE_NOT_MOVING;
	this->firing_state = STATE_NOT_FIRING;
	this->shooting_state = STATE_NOT_SHOOTING;
	this->rotation_state = STATE_NOT_MOVING;
}

Player::Player(Player&& from){
	this->id = from.id;
	
	this->vidas = from.vidas;
	
	this->health = from.health;
	this->has_key = from.has_key;
	this->puntaje = from.puntaje;
	this->max_bullets = from.max_bullets;
	this->bullets = from.bullets;
	this->selected_weapon_idx = from.selected_weapon_idx;
	this->previous_weapon_idx = from.previous_weapon_idx;
	this->movement_state = from.movement_state;
	this->firing_state = from.firing_state;
	this->before_respawn = from.before_respawn;
	this->shooting_state = from.shooting_state;
	this->rotation_state = from.rotation_state;

	this->armas[0] = from.armas[0];
	this->armas[1] = from.armas[1];
	this->armas[2] = from.armas[2];
	this->armas[3] = from.armas[3];
	this->armas[4] = from.armas[4];
	
	from.armas[0] = NULL;
	from.armas[1] = NULL;
	from.armas[2] = NULL;
	from.armas[3] = NULL;
	from.armas[4] = NULL;	
	
}

float Player::getShootTimeout() {
	if(this->armas[this->selected_weapon_idx] == NULL) 
		return 0;
	return this->armas[this->selected_weapon_idx]->getCadencia();
}

int Player::getWeaponAttackRange() {
	if(this->armas[this->selected_weapon_idx] == NULL) 
		return 0;
	return this->armas[this->selected_weapon_idx]->getAttackRange();
}

bool Player::aimWeapon(float ort_dist, float target_dist) {
	if(this->armas[this->selected_weapon_idx] == NULL) {
		return false;
	}
	return this->armas[this->selected_weapon_idx]->aimWeapon(ort_dist, target_dist);
}

//si el jugador es muerto como resultado de perder vida, devuelvo true.
bool Player::loseHealth(int amount) {
	if (this->before_respawn) return false;
	this->health = this->health - amount;
	std::cout << "Player was attacked --> health: " << this->health << std::endl;
	this->receivedDamage = true;
	if (this->health <= 0 && this->vidas > 0) {
		this->died = true;
		this->before_respawn = true;
		this->health = 20;
		this->vidas--;
		this->has_key = false;
		this->bullets = 8;
		this->puntaje = 0;
		this->selected_weapon_idx = 1;
		for (int i = 2; i < this->armas.size(); i++){
			if (this->armas[i] != NULL){
				delete this->armas[i];
				this->armas[i] = NULL;
			}
		}
		this->movement_state = STATE_NOT_MOVING;
		std::cout << "LIVES: " << this->vidas << std::endl;
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
		this->pickedUpLife = true;
		return true;
	}
	return false;
}

bool Player::addScore(int amount) {
	this->puntaje += amount;
	this->pickedUpTreasure = true;
	return true;
}

bool Player::loseBullet() {
	if(this->selected_weapon_idx == 0) return false;
	if(this->bullets > 0) this->bullets--;
	if(this->bullets == 0 && selected_weapon_idx != 0) {
		this->previous_weapon_idx = this->selected_weapon_idx;
		this->selected_weapon_idx = 0;
	}
	return true;
}

bool Player::addBullets(int amount) {
	if (this->bullets == 0) this->selected_weapon_idx = this->previous_weapon_idx;
	if( this->bullets < this->max_bullets) {
		this->bullets += amount;
		if(this->bullets > this->max_bullets) this->bullets = this->max_bullets;
		this->pickedUpBullets = true;
		return true;
	}
	return false;
}

bool Player::addWeapon(Arma* arma) {
	if (arma->getIndex() < this->armas.size() && this->armas[arma->getIndex()] == NULL ){
		return this->_addWeapon(arma->getIndex(),arma);
	}
	return false;
}

bool Player::_addWeapon(int idx, Arma* arma) {
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
	if(this->armas[weapon_idx] == NULL) return false;
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

bool Player::changeShootingState(ShootingState state) {
	this->shooting_state = state;
	return true;
}

ShootingState Player::getCurrentShootingState() {
	return this->shooting_state;
}

bool Player::changeFiringState(FiringState state) {
	this->firing_state = state;
	return true;
}
    
FiringState Player::getCurrentFiringState() {
	return this->firing_state;
}

bool Player::changeRotationState(MovementState state){
	this->rotation_state = state;
	return true;
}

MovementState Player::getCurrentRotationState(){
	return this->rotation_state;
}

bool Player::receivedDamageInStep() {
	return this->receivedDamage;
}

bool Player::diedInStep(){
	return this->died;
}

bool Player::pickedUpTreasureInStep(){
	return this->pickedUpTreasure;
}

bool Player::pickedUpBulletsInStep(){
	return this->pickedUpBullets;
}

bool Player::pickedUpLifeInStep(){
	return this->pickedUpLife;
}

void Player::resetStepEvents(){
	this->receivedDamage = false;
	this->died = false;
	this->pickedUpTreasure = false;
	this->pickedUpBullets = false;
	this->pickedUpLife = false;
}

void Player::respawn() {
	this->before_respawn = false;
}

bool Player::outGame() {
	return this->before_respawn;
}

Player::~Player(){
	for (int i =0; i < AMOUNT_WEAPONS; i++){
		if (this->armas[i] != NULL){
			delete this->armas[i];
			this->armas[i] = NULL;
		}
	}
}
