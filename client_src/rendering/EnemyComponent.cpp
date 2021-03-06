#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(SDL_Renderer* renderer, YAML::Node spec) {
	std::string directory = spec["directory"].as<std::string>();

	YAML::Node idle_animations_spec = spec["idle_animations"];
	this->loadIdleAnimations(renderer, directory, idle_animations_spec);

	YAML::Node moving_animations_spec = spec["moving_animations"];
	this->loadMovingAnimations(renderer, directory, moving_animations_spec);

	this->dying_animation = this->buildAnimation(renderer, directory,
																      				 spec["dying_animation"]);

	this->shooting_animation = this->buildAnimation(renderer, directory,
																	      				  spec["shooting_animation"]);

	this->damage_animation = this->buildAnimation(renderer, directory,
																      				  spec["damage_animation"]);

	std::string dying_sound_path = spec["dying_sound"].as<std::string>();
	this->dying_sound = this->buildSoundEffect(directory + dying_sound_path);
      
	std::string shooting_sound_path = spec["shooting_sound"].as<std::string>();
	this->shooting_sound = this->buildSoundEffect(directory + shooting_sound_path);
      
	std::string damage_sound_path = spec["damage_sound"].as<std::string>();
	this->damage_sound = this->buildSoundEffect(directory + damage_sound_path);
}

EnemyComponent::~EnemyComponent() {
	for (Animation* animation : this->idle_animations) delete animation;
	for (Animation* animation : this->moving_animations) delete animation;

	delete this->dying_animation;
	delete this->shooting_animation;
	delete this->getting_damage_animation;

	delete this->dying_sound;
	delete this->shooting_sound;
	delete this->getting_damage_sound;
}

Animation* EnemyComponent::buildAnimation(SDL_Renderer* renderer,
												 								  std::string directory, 
												 								  YAML::Node spec) {
	std::vector<std::string> frame_paths;
	for (int i = 0; i < spec.size(); i++) {
		std::string filename = spec[i].as<std::string>();
		std::string frame_path = directory + filename;
		frame_paths.push_back(filepath);
	}
	return new Animation(renderer, frame_paths);
}

SoundEffect* EnemyComponent::buildSoundEffect(std::string path) {
	std::string sound_filename = spec.as<std::string()>;
	return new SoundEffect(sound_filename.c_str());
	/*
	std::string getting_damage_sound_filename = spec["getting_damage_sound"].as<std::string>();
	std::string getting_damage_sound_path = directory + getting_damage_sound_filename;
	this->getting_damage_sound = new SoundEffect(getting_damage_sound_path.c_str());
	*/
}

void EnemyComponent::renderIdle(SDL_Renderer* renderer, 
																std::vector<float>& z_buffer,
																float z_depth, int x_pos, int y_pos, 
																int width, int height,
																int frame, SpriteAngle view_angle) {

}

void EnemyComponent::renderMoving(SDL_Renderer* renderer,
																	std::vector<float>& z_buffer,
																	float z_depth, int x_pos, int y_pos, 
																	int width, int height,
																	int frame, SpriteAngle view_angle) {

}

void EnemyComponent::renderDying(SDL_Renderer* renderer,
																 std::vector<float>& z_buffer,
								 								 float z_depth, int x_pos, int y_pos, 
								 								 int width, int height, int frame) {

}

void EnemyComponent::renderShooting(SDL_Renderer* renderer,
																		std::vector<float>& z_buffer,
									  								float z_depth, int x_pos, int y_pos, 
									  								int width, int height, int frame) {

}

void EnemyComponent::renderGettingShot(SDL_Renderer* renderer,
																			 std::vector<float>& z_buffer,
											 								 float z_depth, int x_pos, int y_pos, 
											 								 int width, int height, int frame) {

}
