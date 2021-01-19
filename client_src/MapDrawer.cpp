#include <iostream>

#include "MapDrawer.h"

#define WALL_HEIGHT 1.5

MapDrawer::MapDrawer(int screen_width, int screen_height, float fov,
										 std::vector<Texture*>& wall_textures)
	: screen_width(screen_width), screen_height(screen_height), fov(fov),
		wall_textures(wall_textures) { }

MapDrawer::~MapDrawer() { }

std::vector<float> MapDrawer::draw(SDL_Renderer* renderer, Map& map,
										 							 Vector position, float view_angle) {
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
		int l = std::abs(WALL_HEIGHT * projection_distance / distance); 
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
