#include <iostream>

#include "MapDrawer.h"

#define WALL_HEIGHT 1.5

MapDrawer::MapDrawer(YAML::Node& config, std::vector<Texture*>& wall_textures)
	: screen_width(config["window"]["width"].as<int>()), 
		screen_height(config["window"]["height"].as<int>()), 
		fov(config["graphics"]["FOV"].as<float>()),
		wall_height(config["graphics"]["wall_height"].as<float>()),
		wall_textures(wall_textures) { }

MapDrawer::~MapDrawer() { }

std::vector<float> MapDrawer::draw(SDL_Renderer* renderer, Map& map,
										 							 Vector position, float view_angle) {
	SDL_Rect top_half { 0, 0, this->screen_width, (this->screen_height)/2 };
	SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
	SDL_RenderFillRect(renderer, &top_half);

	SDL_Rect bottom_half { 0, (this->screen_height)/2,
												 this->screen_width, (this->screen_height)/2 };
	SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
	SDL_RenderFillRect(renderer, &bottom_half);

	std::vector<float> z_buffer;
	z_buffer.reserve(this->screen_width);

	float a_increment = (this->fov/this->screen_width);
	float initial_angle = view_angle + (this->fov/2);
	float final_angle = view_angle - (this->fov/2);

	float projection_distance = (this->screen_width/2)/tan(this->fov/2);

	int x = 0;
	for (float a = initial_angle; a > final_angle; a -= a_increment) {
		RayHit hit = this->ray_caster.castRay(map, position, a);

		float distance = cos(a - view_angle) * hit.distance;
		int l = std::abs(this->wall_height * projection_distance / distance);
		/* TODO: Ver cuales son los casos en los cuales esto da negativo 
			así no hay que hacer std::abs a lo bruto.
																			- Pablo (14/01/2020)				*/

		Texture* wall_texture = this->wall_textures[0];
		wall_texture->renderTexel(renderer, x, hit.texel, 
														  this->screen_height, l, hit.side);

		z_buffer[x] = hit.distance;
		x++;
	}
	return z_buffer;
}
