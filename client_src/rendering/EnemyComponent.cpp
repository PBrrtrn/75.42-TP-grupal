#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(SDL_Renderer* renderer, YAML::Node spec) {
	std::string directory = spec["directory"].as<std::string>();

	this->idle_animations = this->buildAnimations(renderer, directory,
																								spec["idle_animations"]);

	this->moving_animations = this->buildAnimations(renderer, directory,
																									spec["moving_animations"]);

	this->dying_steps = spec["dying_animation"].size();
	this->dying_animation = this->buildAnimation(renderer, directory,
																      				 spec["dying_animation"]);

	this->shooting_steps = spec["shooting_animation"].size();
	this->shooting_animation = this->buildAnimation(renderer, directory,
																	      				  spec["shooting_animation"]);

	this->damage_steps = spec["damage_animation"].size();
	this->damage_animation = this->buildAnimation(renderer, directory,
																      				  spec["damage_animation"]);

	std::string sound_path;
	sound_path = spec["dying_sound"].as<std::string>();
	this->dying_sound = new SoundEffect((directory + sound_path).c_str());
      
	sound_path = spec["shooting_sound"].as<std::string>();
	this->dying_sound = new SoundEffect((directory + sound_path).c_str());
      
	sound_path = spec["damage_sound"].as<std::string>();
	this->dying_sound = new SoundEffect((directory + sound_path).c_str());
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

	ptr = buildAnimation(renderer, directory, spec["three_quarters_right"]);
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

void renderDying(SDL_Renderer* renderer, std::vector<float> z_buffer,
								 float z_depth, int x_pos, int y_pos,
								 int width, int height, int elapsed_steps) {

}

void renderDamage(SDL_Renderer* renderer, std::vector<float> z_buffer,
								  float z_depth, int x_pos, int y_pos,
								  int width, int height, int elapsed_steps) {

}

void renderShooting(SDL_Renderer* renderer, std::vector<float> z_buffer,
								    float z_depth, int x_pos, int y_pos,
								    int width, int height, int elapsed_steps) {

}

void renderIdle(SDL_Renderer* renderer, std::vector<float> z_buffer,
								float z_depth, int x_pos, int y_pos, SpriteAngle angle,
								int width, int height, int elapsed_steps) {
	this->idle_animations[angle]->render(renderer, z_buffer, z_depth, 
																			 x_pos, y_pos, width, height, 
																			 elapsed_steps);
}

void renderMoving(SDL_Renderer* renderer, std::vector<float> z_buffer,
								  float z_depth, int x_pos, int y_pos, SpriteAngle angle,
								  int width, int height, int elapsed_steps) {

}

int dyingSteps() {
	return this->dying_steps;
}

int shootingSteps() {
	return this->shooting_steps;
}

int damageSteps() {
	return this->damage_steps;
}
