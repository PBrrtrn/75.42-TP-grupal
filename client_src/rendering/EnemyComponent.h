#ifndef __ENEMY_COMPONENT_H__
#define __ENEMY_COMPONENT_H__

#include <vector>

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>

#include "Animation.h"
#include "SoundEffect.h"

enum SpriteAngle {
	FRONT,
	QUARTER_RIGHT,
	PROFILE_RIGHT,
	THREE_QUARTERS_RIGHT,
	BACK,
	THREE_QUARTERS_LEFT,
	PROFILE_LEFT,
	QUARTER_LEFT
};

enum State { IDLE, MOVING, DYING, SHOOTING, DAMAGE };

class EnemyComponent {
private:
	std::vector<Animation*> idle_animations;
	std::vector<Animation*> moving_animations;

	Animation* dying_animation;
	Animation* shooting_animation;
	Animation* damage_animation;

	SoundEffect* dying_sound;
	SoundEffect* shooting_sound;
	SoundEffect* damage_sound;

	std::vector<Animation*> buildAnimations(SDL_Renderer* renderer, 
											    								std::string directory, 
											    								YAML::Node spec);
	Animation* buildAnimation(SDL_Renderer* renderer,
													  std::string directory,
													  YAML::Node spec);
	SoundEffect* buildSoundEffect(std::string path);
public:
	EnemyComponent(SDL_Renderer* renderer, YAML::Node spec);
	~EnemyComponent();
	void renderDying(SDL_Renderer* renderer, std::vector<float> z_buffer,
									 float z_depth, int x_pos, int y_pos,
									 int width, int height, int elapsed_steps);
	void renderDamage(SDL_Renderer* renderer, std::vector<float> z_buffer,
									  float z_depth, int x_pos, int y_pos,
									  int width, int height, int elapsed_steps);
	void renderShooting(SDL_Renderer* renderer, std::vector<float> z_buffer,
									    float z_depth, int x_pos, int y_pos,
									    int width, int height, int elapsed_steps);
	void renderIdle(SDL_Renderer* renderer, std::vector<float> z_buffer,
									float z_depth, int x_pos, int y_pos, SpriteAngle angle,
									int width, int height, int elapsed_steps);
	void renderMoving(SDL_Renderer* renderer, std::vector<float> z_buffer,
									  float z_depth, int x_pos, int y_pos, SpriteAngle angle,
									  int width, int height, int elapsed_steps);
	int dyingSteps();
	int shootingSteps();
	int damageSteps();
	/* Si es necesario repetir frames de la animación en varios steps,
	el parámetro steps_per_frame debería existir en EnemyComponent y
	cargarse del nodo de configuracion														  */
};

#endif
