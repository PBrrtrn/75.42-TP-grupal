#include <iostream>

#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(SDL_Renderer* renderer, YAML::Node spec) {
	std::string directory = spec["directory"].as<std::string>();

	this->idle_steps_per_frame = spec["idle_steps_per_frame"].as<int>();
	this->idle_animations = this->buildAnimations(renderer, directory,
																								spec["idle_animations"]);

	this->moving_steps_per_frame = spec["moving_steps_per_frame"].as<int>();
	this->moving_animations = this->buildAnimations(renderer, directory,
																									spec["moving_animations"]);

	this->dying_steps_per_frame = spec["dying_steps_per_frame"].as<int>();
	this->dying_animation = this->buildAnimation(renderer, directory,
																      				 spec["dying_animation"]);

	this->shooting_steps_per_frame = spec["shooting_steps_per_frame"].as<int>();
	this->shooting_animation = this->buildAnimation(renderer, directory,
																	      				  spec["shooting_animation"]);

	this->damage_steps_per_frame = spec["damage_steps_per_frame"].as<int>();
	this->damage_animation = this->buildAnimation(renderer, directory,
																      				  spec["damage_animation"]);

	std::string sound_path;
	sound_path = spec["dying_sound"].as<std::string>();
	this->dying_sound = new SoundEffect((directory + sound_path).c_str());
      
	sound_path = spec["shooting_sound"].as<std::string>();
	this->shooting_sound = new SoundEffect((directory + sound_path).c_str());
      
	sound_path = spec["damage_sound"].as<std::string>();
	this->damage_sound = new SoundEffect((directory + sound_path).c_str());
}

EnemyComponent::~EnemyComponent() {
	for (Animation* animation : this->idle_animations) delete animation;
	for (Animation* animation : this->moving_animations) delete animation;

	delete this->dying_animation;
	delete this->shooting_animation;
	delete this->damage_animation;

	delete this->dying_sound;
	delete this->shooting_sound;
	delete this->damage_sound;
}

std::vector<Animation*> EnemyComponent::buildAnimations(SDL_Renderer* renderer,
																												std::string directory,
																												YAML::Node spec) {
	std::vector<Animation*> animations;

	Animation* ptr;

	ptr = buildAnimation(renderer, directory, spec["front"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["quarter_right"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["profile_right"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["three_quarters_right"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["back"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["three_quarters_left"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["profile_left"]);
	animations.push_back(ptr);

	ptr = buildAnimation(renderer, directory, spec["quarter_left"]);
	animations.push_back(ptr);

	return animations;
}

Animation* EnemyComponent::buildAnimation(SDL_Renderer* renderer,
												 								  std::string directory, 
												 								  YAML::Node spec) {
	std::vector<std::string> frame_paths;
	for (int i = 0; i < spec.size(); i++) {
		std::string filename = spec[i].as<std::string>();
		std::string frame_path = directory + filename;
		frame_paths.push_back(frame_path);
	}
	return new Animation(renderer, frame_paths);
}

SoundEffect* EnemyComponent::buildSoundEffect(std::string path) {
	return new SoundEffect(path.c_str());
}

void EnemyComponent::renderDying(SDL_Renderer* renderer, 
																 std::vector<float> z_buffer,
								 								 float z_depth, int x_pos, int y_pos,
								 								 int width, int height, int elapsed_steps) {
	int frame = elapsed_steps/this->dying_steps_per_frame;
	this->dying_animation->renderTexels(renderer, frame, 
																			z_buffer, z_depth, 
																			x_pos, y_pos, width, height);
}

void EnemyComponent::renderDamage(SDL_Renderer* renderer, 
																	std::vector<float> z_buffer,
								  								float z_depth, int x_pos, int y_pos,
								  								int width, int height, int elapsed_steps) {
	int frame = elapsed_steps/this->damage_steps_per_frame;
	this->damage_animation->renderTexels(renderer, frame, 
																			 z_buffer, z_depth, 
																			 x_pos, y_pos, width, height);
}

void EnemyComponent::renderShooting(SDL_Renderer* renderer, 
																	  std::vector<float> z_buffer,
								    								float z_depth, int x_pos, int y_pos,
								    								int width, int height, int elapsed_steps) {
	int frame = elapsed_steps/this->shooting_steps_per_frame;
	this->shooting_animation->renderTexels(renderer, frame, 
																				 z_buffer, z_depth, 
																				 x_pos, y_pos, width, height);
}

void EnemyComponent::renderIdle(SDL_Renderer* renderer, 
																std::vector<float> z_buffer,
																float z_depth, int x_pos, int y_pos, 
																int angle, int width, int height, 
																int elapsed_steps) {
	int frame = elapsed_steps/this->idle_steps_per_frame;
	this->idle_animations[angle]->renderTexels(renderer, frame, 
																						 z_buffer, z_depth, 
																						 x_pos, y_pos, width, height);
}

void EnemyComponent::renderMoving(SDL_Renderer* renderer, 
																	std::vector<float> z_buffer,
								  								float z_depth, int x_pos, int y_pos, 
								  								int angle, int width, int height, 
								  								int elapsed_steps) {
	int frame = elapsed_steps/this->moving_steps_per_frame;
	this->moving_animations[angle]->renderTexels(renderer, frame, 
																						   z_buffer, z_depth, 
																						   x_pos, y_pos, width, height);
}

void EnemyComponent::playDyingSound() {
	this->dying_sound->play();
}

void EnemyComponent::playDamageSound() {
	this->damage_sound->play();
}

void EnemyComponent::playShootingSound() {
	this->shooting_sound->play();
}

int EnemyComponent::dyingSteps() {
	return this->dying_steps_per_frame * this->dying_animation->framesCount();
}

int EnemyComponent::shootingSteps() {
	return this->shooting_steps_per_frame * this->shooting_animation->framesCount();
}

int EnemyComponent::damageSteps() {
	return this->damage_steps_per_frame * this->damage_animation->framesCount();
}
