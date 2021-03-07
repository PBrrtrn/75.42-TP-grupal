#ifndef __ENEMY_ENTITY_H__
#define __ENEMY_ENTITY_H__

#include <vector>
#include <SDL2/SDL.h>

#include "EnemyComponent.h"
#include "../../common_src/Vector.h"

enum EnemyType { DOG, GUARD, SS, OFFICIAL }:

class EnemyEntity {
private:
	std::vector<EnemyComponent*>& components;
	bool moving;
	bool dying;
	bool shooting;
	bool receiving_damage;
	int elapsed_steps;
public:
	EnemyType type;
	Vector position;
	Vector direction; // Ver si no conviene usar un float...
	EnemyEntity(std::vector<EnemyComponent*>& components);
	~EnemyEntity();
	void render(SDL_Renderer* renderer, std::vector<float>& z_buffer,
							float z_depth, int x_pos, int y_pos, 
							int width, int height, SpriteAngle angle);
	void setDying();
	void setReceivingDamage();
	void setFiring();
};

#endif