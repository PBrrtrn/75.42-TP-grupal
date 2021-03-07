#include "shoot_event.h"

ShootEvent::ShootEvent(Shoot* shoot, void (Shoot::*shoot_func)(GameStatus& gs, int id), const int id, GameStatus& gs): 
    shoot_func(shoot_func), 
    active(false), 
    param(id), gs(gs), 
    shoot(shoot), 
    elapsed(0),
    last_run_time(0), 
    timeout(0)
    {}

void ShootEvent::activate(double timeout) {
    this->timeout = timeout;
    if (this->timeout <= 0) {
        (shoot->*shoot_func)(this->gs, this->param);
    } else {
        this->active = true;
        if (this->elapsed - this->last_run_time >= this->timeout ||
            (this->elapsed == 0 && this->last_run_time == 0)) {
            (shoot->*shoot_func)(this->gs, this->param);
            this->last_run_time = this->elapsed;
        }
    }
}

void ShootEvent::deactivate() {
    this->active = false;
}

bool ShootEvent::update(double delta) {
    this->elapsed = delta;
    if (this->timeout <= 0 || !this->active ) return false;
    if (this->elapsed - this->last_run_time >= this->timeout) {
        (shoot->*shoot_func)(this->gs, this->param);
        this->last_run_time = this->elapsed;
        return true;
    } else {
        return false;
    }
}

ShootEvent::~ShootEvent() {}