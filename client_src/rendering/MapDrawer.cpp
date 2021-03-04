#include <iostream>
#include <math.h>

#include "MapDrawer.h"

#define WALL_HEIGHT 1.5

MapDrawer::MapDrawer(YAML::Node& config, Map& map,
                     std::vector<Texture*>& wall_textures,
                     std::vector<Texture*>& item_sprites,
                     std::vector<Animation*>& enemy_animations)
: screen_width(config["window"]["width"].as<int>()), 
  screen_height(config["window"]["height"].as<int>()), 
  fov(config["graphics"]["FOV"].as<float>()),
  wall_height(config["graphics"]["wall_height"].as<float>()),
  wall_textures(wall_textures), item_sprites(item_sprites),
  enemy_animations(enemy_animations), map(map) { }

MapDrawer::~MapDrawer() { }

void MapDrawer::draw(SDL_Renderer* renderer, Vector position, float view_angle,
                     std::vector<ItemListElement>& items,
                     std::vector<PlayerListItem>& enemies) {
  this->drawFloors(renderer);

  float a_increment = (this->fov/this->screen_width);
  float initial_angle = view_angle + (this->fov/2);
  float final_angle = view_angle - (this->fov/2);

  float projection_distance = (this->screen_width/2)/tan(this->fov/2);

  int x = 0;
  std::vector<float> z_buffer;
  z_buffer.reserve(this->screen_width);
  for (float a = initial_angle; a > final_angle; a -= a_increment) {
    RayHit hit = this->ray_caster.castRay(this->map, position, a);

    float distance = cos(a - view_angle) * hit.distance;
    int l = this->wall_height * projection_distance / distance;

    Texture* wall_texture = this->wall_textures[0];
    wall_texture->renderTexel(renderer, x, hit.texel,
                              this->screen_height, l, hit.side);

    z_buffer.push_back(hit.distance);
    x++;
  }

  this->drawEnemies(renderer, position, view_angle, enemies, z_buffer);
  this->drawItems(renderer, position, view_angle, items, z_buffer);
}

void MapDrawer::drawFloors(SDL_Renderer* renderer) {
  SDL_Rect top_half { 0, 0, this->screen_width, (this->screen_height)/2 };
  SDL_SetRenderDrawColor(renderer, 130, 130, 130, 255);
  SDL_RenderFillRect(renderer, &top_half);

  SDL_Rect bottom_half { 0, (this->screen_height)/2,
                         this->screen_width, (this->screen_height)/2 };
  SDL_SetRenderDrawColor(renderer, 90, 90, 90, 255);
  SDL_RenderFillRect(renderer, &bottom_half);
}

void MapDrawer::drawEnemies(SDL_Renderer* renderer,
                            Vector position, float view_angle,
                            std::vector<PlayerListItem>& enemies,
                            std::vector<float> z_buffer) {
  float view_y = sin(view_angle);
  float view_x = cos(view_angle);
  Vector plane(view_angle + M_PI/2);
  plane = plane * ((this->fov*180) / (100*M_PI));
  for (PlayerListItem& enemy : enemies) {
    Vector enemy_dir { enemy.position.x - position.x,
                       position.y - enemy.position.y };
    float transf_x = view_x * enemy_dir.y - view_y * enemy_dir.x;
    float transf_y = plane.y * enemy_dir.x - plane.x * enemy_dir.y;

    if (transf_y > 0.1) {
      int sprite_width = int(this->screen_width/transf_y);
      int sprite_height = int(this->screen_height/transf_y);

      int sprite_x = (this->screen_width/2) * (1 - transf_x/transf_y);
      int sprite_y = (this->screen_height - sprite_height)/2;

      Animation* animation = enemy_animations[0];
      animation->renderTexels(renderer, z_buffer, transf_y, 
                              sprite_x, sprite_y,
                              sprite_width, sprite_height);
    }
  }
}

void MapDrawer::drawItems(SDL_Renderer* renderer, 
                          Vector position, float view_angle,
                          std::vector<ItemListElement>& items,
                          std::vector<float> z_buffer) {
  float view_y = sin(view_angle);
  float view_x = cos(view_angle);
  Vector plane(view_angle + M_PI/2);
  plane = plane * ((this->fov*180) / (100*M_PI));

  for (ItemListElement& item : items) {
    std::cout << "current pos: (" << position.x << ", " << position.y << ")" << std::endl;
    std::cout << "item pos: (" << item.pos.x << ", " << item.pos.y << ")" << std::endl;
    Vector item_dir { item.pos.x - position.x,
                      position.y - item.pos.y };
    float transf_x = view_x * item_dir.y - view_y * item_dir.x;
    float transf_y = plane.y * item_dir.x - plane.x * item_dir.y;

    if (transf_y > 0.1) {
      int sprite_width = int(this->screen_width/transf_y);
      int sprite_height = int(this->screen_height/transf_y);

      int sprite_x = (this->screen_width/2) * (1 - transf_x/transf_y);
      int sprite_y = (this->screen_height - sprite_height)/2;

      // Texture* sprite = this->item_sprites[item.type];
      Texture* sprite = this->item_sprites[0];
      sprite->renderTexels(renderer, z_buffer, transf_y,
                              sprite_x, sprite_y,
                              sprite_width, sprite_height);
    }
  }
}