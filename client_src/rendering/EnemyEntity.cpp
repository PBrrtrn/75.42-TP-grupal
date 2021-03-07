#include "EnemyEntity.h"

EnemyEntity::EnemyEntity(std::vector<EnemyComponent*>& components)
: components(components), moving(false), dying(false),
shooting(false), receiving_damage(false), elapsed_steps(0) { }

EnemyEntity::~EnemyEntity() { }

EnemyEntity::render(SDL_Renderer* renderer, std::vector<float>& z_buffer,
										float z_depth, int x_pos, int y_pos, 
										int width, int height, SpriteAngle angle) {
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
			this->dying = false;
			this->elapsed_steps = 0;
		}
	} else if (this->shooting) {
		component->renderShooting(renderer, z_buffer, z_depth, x_pos, y_pos,
													    width, height, elapsed_steps);
		if (this->elapsed_steps == component->shootingSteps()) {
			this->dying = false;
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

