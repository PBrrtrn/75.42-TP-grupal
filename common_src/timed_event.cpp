#include "timed_event.h"

TimedEvent::TimedEvent(Shoot* shoot, void (Shoot::*function)(GameStatus& gs, int id), const int id, GameStatus& gs): 
    function(function), 
    active(false), 
    param(id), gs(gs), 
    shoot(shoot), 
    elapsed(0),
    last_shoot_time(0)
    {}

void TimedEvent::activate(double timeout) {
    this->timeout = timeout;
    if (this->timeout <= 0) {
        (shoot->*function)(this->gs, this->param);
    } else {
        this->active = true;
        if (this->elapsed - this->last_shoot_time >= this->timeout ||
            (this->elapsed == 0 && this->last_shoot_time == 0)) {
            (shoot->*function)(this->gs, this->param);
            this->last_shoot_time = this->elapsed;
        }
    }
}

void TimedEvent::deactivate() {
    this->active = false;
}

bool TimedEvent::update(double delta) {
    this->elapsed = delta;
    if (this->timeout <= 0 || !this->active ) return false;
    if (this->elapsed - this->last_shoot_time >= this->timeout) {
        (shoot->*function)(this->gs, this->param);
        this->last_shoot_time = this->elapsed;
        return true;
    } else {
        return false;
    }
}

TimedEvent::~TimedEvent() {}