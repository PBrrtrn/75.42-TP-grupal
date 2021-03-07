#include "respawn_event.h"

RespawnEvent::RespawnEvent(Player* player, void (Player::*player_func)(void)): 
    player_func(player_func), 
    player(player), 
    elapsed(0),
    timeout(0)
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
    if (this->elapsed >= this->timeout) {
        (player->*player_func)();
        return true;
    } else {
        return false;
    }
}

RespawnEvent::~RespawnEvent() {}