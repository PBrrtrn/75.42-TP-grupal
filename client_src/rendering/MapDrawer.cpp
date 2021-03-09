#include <iostream>
#include <math.h>

#include "MapDrawer.h"

#define WALL_HEIGHT 1.5

MapDrawer::MapDrawer(YAML::Node& config, Map& map,
                     std::vector<Texture*>& wall_textures,
                     std::vector<Texture*>& item_sprites)
: screen_width(config["window"]["width"].as<int>()), 
  screen_height(config["window"]["height"].as<int>()), 
  fov(config["graphics"]["FOV"].as<float>()),
  wall_height(config["graphics"]["wall_height"].as<float>()),
  wall_textures(wall_textures), item_sprites(item_sprites),
  map(map) { }

MapDrawer::~MapDrawer() { }

void MapDrawer::draw(SDL_Renderer* renderer, Vector position, float view_angle,
                     std::vector<ItemListElement>& items,
                     std::unordered_map<char, EnemyEntity*> enemies) {
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

    Texture* wall_texture = this->wall_textures[hit.texture];
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
                            std::unordered_map<char, EnemyEntity*> enemies,
                            std::vector<float> z_buffer) {
  float view_y = sin(view_angle);
  float view_x = cos(view_angle);
  Vector plane(view_angle + M_PI/2);
  plane = plane * ((this->fov*180.0) / (100.0*M_PI));

  float inv_det = 1.0 / fabs((plane.x * view_y) - (plane.y * view_x));

  for (auto& it : enemies) {
    EnemyEntity* enemy = it.second;

    Vector enemy_dir { enemy->position.x - position.x,
                       position.y - enemy->position.y };
    float transf_x = inv_det * (view_x * enemy_dir.y - view_y * enemy_dir.x);
    float transf_y = inv_det * (plane.y * enemy_dir.x - plane.x * enemy_dir.y);

    if (transf_y > 0.1) {
      float angle_to_enemy = enemy_dir.getAngle();
      float enemy_view_angle = enemy->direction.getAngle();

      float p_angle = enemy_view_angle - angle_to_enemy;
      /* No funciona este cálculo para todos los vectores posibles
         por ejemplo, cuando los dos tienen direccion (-1,0) el ángulo
         se vuelve cerca de -6.28 - habría que analizar los casos posibles */

      int perspective = 0;
      if ((5*M_PI/6 < p_angle) || (p_angle < -5*M_PI/6))
        perspective = 0; // front
      else if ((-5*M_PI/6 < p_angle) && (p_angle < -2*M_PI/3))
        perspective = 1; // 1/4 right
      else if ((-2*M_PI/3 < p_angle) && (p_angle < -M_PI/2))
        perspective = 2; // profile right
      else if ((-M_PI/3 < p_angle) && (p_angle < -M_PI/6))
        perspective = 3; // 3/4 right
      else if ((-M_PI/6 < p_angle) && (p_angle < M_PI/6))
        perspective = 4; // back
      else if ((M_PI/6 < p_angle) && (p_angle < M_PI/3))
        perspective =  5; // 3/4 left
      else if ((M_PI/3 < p_angle) && (p_angle < 2*M_PI/3))
        perspective = 6; // profile left
      else if ((2*M_PI/3 < p_angle) && (p_angle < 5*M_PI/6))
        perspective = 7; // 1/4 left

      int sprite_width = abs(int(this->screen_width/transf_y));
      int sprite_height = 2 * abs(int(this->screen_height/transf_y));

      int sprite_x = (this->screen_width/2) * (1 - transf_x/transf_y);
      int sprite_y = (this->screen_height - sprite_height)/2;

      enemy->render(renderer, z_buffer, transf_y, sprite_x, sprite_y,
                    sprite_width, sprite_height, perspective);
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

  float inv_det = 1.0 / fabs((plane.x * view_y) - (plane.y * view_x));

  for (ItemListElement& item : items) {
    Vector item_dir { item.pos.x - position.x,
                      position.y - item.pos.y };
    float transf_x = inv_det * (view_x * item_dir.y - view_y * item_dir.x);
    float transf_y = inv_det * (plane.y * item_dir.x - plane.x * item_dir.y);

    if (transf_y > 0.1) {
      int sprite_width = int(this->screen_width/transf_y);
      int sprite_height = 2*int(this->screen_height/transf_y);

      int sprite_x = (this->screen_width/2) * (1 - transf_x/transf_y);
      int sprite_y = (this->screen_height - sprite_height)/2;

      Texture* sprite = this->item_sprites[item.type];
      sprite->renderTexels(renderer, z_buffer, transf_y,
                           sprite_x, sprite_y,
                           sprite_width, sprite_height);
    }
  }
}