#include "timed_event.h"

TimedEvent::TimedEvent(Shoot* shoot, void (Shoot::*function)(GameStatus& gs, int id), const int id, GameStatus& gs): 
    elapsed(0), function(function), active(false), param(id), gs(gs), shoot(shoot) {}

void TimedEvent::activate(float timeout) {
    this->timeout = timeout;
    this->active = true;
}

void TimedEvent::deactivate() {
    this->active = false;
}

bool TimedEvent::update(float delta) {
    if (!this->active) return false;
    elapsed += delta;
    if (elapsed >= timeout) {
        (shoot->*function)(this->gs, this->param);
        return true;
    } else {
        return false;
    }
}

TimedEvent::~TimedEvent() {}