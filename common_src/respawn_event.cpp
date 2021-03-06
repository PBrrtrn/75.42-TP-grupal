#include "respawn_event.h"

RespawnEvent::RespawnEvent(Player* player, void (Player::*player_func)(void)): 
    player_func(player_func), 
    player(player), 
    elapsed(0)
    {}

void RespawnEvent::activate(double timeout) {
    this->timeout = timeout;
    this->active = true;
}

void RespawnEvent::deactivate() {
    this->elapsed = 0;
    this->active = false;
}

bool RespawnEvent::update(double delta) {
    if (!this->active) return false;
    this->elapsed += delta;
    std::cout << "elapsed" << this->elapsed << std::endl;
    std::cout << "timeout" << this->timeout << std::endl;
    if (this->elapsed >= this->timeout) {
        std::cout << "elapsed" << this->elapsed << std::endl;
        std::cout << "timeout" << this->timeout << std::endl;
        (player->*player_func)();
        return true;
    } else {
        return false;
    }
}

RespawnEvent::~RespawnEvent() {}