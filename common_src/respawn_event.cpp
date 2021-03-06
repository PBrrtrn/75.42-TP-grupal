#include "respawn_event.h"

RespawnEvent::RespawnEvent(Player* player, void (Player::*player_func)(void)): 
    player_func(player_func), 
    player(player), 
    elapsed(0),
    last_run_time(0)
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
    this->elapsed = delta;
    if (!this->active) return false;
    if (this->elapsed >= this->timeout) {
        std::cout << "elapsed" << this->elapsed << std::endl;
        std::cout << "timeout" << this->timeout << std::endl;
        (player->*player_func)();
        this->deactivate();
        return true;
    } else {
        return false;
    }
}

RespawnEvent::~RespawnEvent() {}