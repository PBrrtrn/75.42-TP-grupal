#ifndef __TIMED_EVENT_H__
#define __TIMED_EVENT_H__

#include "../server_src/actions/shoot.h"
#include "FiringState.h"
#include <time.h>
//#include "../server_src/games/thread_game.h"

//class ThreadGame;

class TimedEvent {
    private:
        double timeout;
        double elapsed;
        double last_shoot_time;
        Shoot* shoot;
        void (Shoot::*function)(GameStatus& gs, int id);
        bool active;
        const int param;
        GameStatus& gs;
    public:
        TimedEvent(Shoot* shoot, void (Shoot::*function)(GameStatus& gs, int id), const int id, GameStatus& gs);
        void activate(double timeout);
        void deactivate();
        bool update(double delta);
        ~TimedEvent();
};

#endif