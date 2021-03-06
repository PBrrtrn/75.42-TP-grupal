#ifndef __RESPAWN_EVENT_H__
#define __RESPAWN_EVENT_H__

#include "timed_event.h"
#include "../server_src/games/player.h"

class RespawnEvent : public TimedEvent {
    private:
        double timeout;
        double elapsed;
        double last_run_time;
        bool active;

        Player* player;
        void (Player::*player_func)();

    public:
        RespawnEvent(Player* player, void (Player::*player_func)(void));

        void activate(double timeout) override;
        void deactivate() override;
        bool update(double delta) override;

        ~RespawnEvent() override;
};

#endif