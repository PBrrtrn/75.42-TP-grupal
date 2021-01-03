#include "MapDrawer.h"

MapDrawer::MapDrawer(int screen_width, int screen_height, float field_of_view) 
: screen_width(screen_width), screen_height(screen_height),
  field_of_view(field_of_view), z_buffer(screen_width) { }

MapDrawer::~MapDrawer() { }

std::vector<int> MapDrawer::draw(SDL_Renderer* renderer, Map& map,
																 Vector position, float angle) {
	return this->z_buffer;
}
