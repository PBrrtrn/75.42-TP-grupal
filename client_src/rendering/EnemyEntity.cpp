#include <iostream>

#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::vector<EnemyComponent*>& components)
: components(components), moving(false), dying(false),
shooting(false), receiving_damage(false), elapsed_steps(0) { }

EnemyEntity::~EnemyEntity() { }

void EnemyEntity::render(SDL_Renderer* renderer, std::vector<float>& z_buffer,
												 float z_depth, int x_pos, int y_pos, 
												 int width, int height, int view_angle) {
	EnemyComponent* component = this->components[this->type];
	if (this->dying) {
		component->renderDying(renderer, z_buffer, z_depth, x_pos, y_pos,
													 width, height, elapsed_steps);
		if (this->elapsed_steps == component->dyingSteps()) {
			this->dying = false;
			this->elapsed_steps = 0;
		}
	} else if (this->receiving_damage) {
		component->renderDamage(renderer, z_buffer, z_depth, x_pos, y_pos,
													  width, height, elapsed_steps);
		if (this->elapsed_steps == component->damageSteps()) {
			this->receiving_damage = false;
			this->elapsed_steps = 0;
		}
	} else if (this->shooting) {
		component->renderShooting(renderer, z_buffer, z_depth, x_pos, y_pos,
													    width, height, elapsed_steps);
		if (this->elapsed_steps == component->shootingSteps()) {
			this->shooting = false;
			this->elapsed_steps = 0;
		}
	} else if (this->moving) {
		component->renderMoving(renderer, z_buffer, z_depth, x_pos, y_pos,
													  view_angle, width, height, elapsed_steps);
	} else {
		component->renderIdle(renderer, z_buffer, z_depth, x_pos, y_pos, 
													view_angle, width, height, elapsed_steps);
	}
	this->elapsed_steps++;
}

void EnemyEntity::setIdle() {
	this->elapsed_steps = 0;
	this->moving = false;
	this->dying = false;
	this->receiving_damage = false;
	this->shooting = false;
}

void EnemyEntity::setMoving() {
	this->moving = true;
}

void EnemyEntity::setDying() {
	this->elapsed_steps = 0;
	this->dying = true;
	this->components[this->type]->playDyingSound();
}

void EnemyEntity::setReceivingDamage() {
	this->elapsed_steps = 0;
	this->receiving_damage = true;
	this->components[this->type]->playDamageSound();
}

void EnemyEntity::setShooting() {
	this->elapsed_steps = 0;
	this->shooting = true;
	this->components[this->type]->playShootingSound();
}