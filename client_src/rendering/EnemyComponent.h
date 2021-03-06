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

	void loadIdleAnimations(SDL_Renderer* renderer, 
													std::string directory, 
													YAML::Node spec);
	void loadMovingAnimations();
	Animation* buildAnimation(YAML::Node spec,
													  std::string directory,
													  SDL_Renderer* renderer);
	SoundEffect* buildSoundEffect(std::string path);
public:
	EnemyComponent(SDL_Renderer* renderer, YAML::Node spec);
	~EnemyComponent();
	void renderIdle(SDL_Renderer* renderer, std::vector<float>& z_buffer,
									float z_depth, int x_pos, int y_pos, int width, int height,
									int frame, SpriteAngle view_angle);
	void renderMoving(SDL_Renderer* renderer, std::vector<float>& z_buffer,
										float z_depth, int x_pos, int y_pos, int width, int height,
										int frame, SpriteAngle view_angle);
	void renderDying(SDL_Renderer* renderer, std::vector<float>& z_buffer,
									 float z_depth, int x_pos, int y_pos, 
									 int width, int height, int frame);
	void renderShooting(SDL_Renderer* renderer, std::vector<float>& z_buffer,
										  float z_depth, int x_pos, int y_pos, 
										  int width, int height, int frame);
	void renderGettingShot(SDL_Renderer* renderer, std::vector<float>& z_buffer,
												 float z_depth, int x_pos, int y_pos, 
												 int width, int height, int frame);
};

#endif
