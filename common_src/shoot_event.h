#ifndef __SHOOT_EVENT_H__
#define __SHOOT_EVENT_H__

#include "timed_event.h"
#include "../server_src/actions/shoot.h"
#include "FiringState.h"

class ShootEvent : public TimedEvent {
    private:
        double timeout;
        double elapsed;
        double last_run_time;

        bool active;
        const int param;
        GameStatus& gs;
        
        Shoot* shoot;
        void (Shoot::*shoot_func)(GameStatus& gs, int id);

    public:
        ShootEvent(Shoot* shoot, void (Shoot::*shoot_func)(GameStatus& gs, int id), const int id, GameStatus& gs);

        void activate(double timeout) override;
        void deactivate() override;
        bool update(double delta) override;

        ~ShootEvent();
};

#endif