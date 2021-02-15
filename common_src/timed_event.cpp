#include "timed_event.h"

TimedEvent::TimedEvent(Shoot* shoot, void (Shoot::*function)(GameStatus& gs, int id), const int id, GameStatus& gs): 
    elapsed(0), function(function), active(false), param(id), gs(gs), shoot(shoot) {}

void TimedEvent::activate(float timeout) {
    this->timeout = timeout;
    this->active = true;
    (shoot->*function)(this->gs, this->param);
    std::cout << "shoot en te activate" <<std::endl;
}

void TimedEvent::deactivate() {
    this->active = false;
}

bool TimedEvent::update(float delta) {
    //std::cout << "empezando update te" << std::endl;
    if (!this->active) return false;
    elapsed += delta;
    if (elapsed >= timeout) {
        std::cout << "shoot en te update" <<std::endl;
        (shoot->*function)(this->gs, this->param);
        this->elapsed = 0;
        return true;
    } else {
        return false;
    }
}

TimedEvent::~TimedEvent() {}