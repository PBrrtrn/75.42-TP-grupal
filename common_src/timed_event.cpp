#include "timed_event.h"

TimedEvent::TimedEvent(): 
    active(false),  
    elapsed(0),
    last_run_time(0)
    {}

void TimedEvent::activate(double timeout) {
    this->timeout = timeout;
}

void TimedEvent::deactivate() {
    this->active = false;
}

bool TimedEvent::update(double delta) {
    this->elapsed = delta;
    return false;
}

TimedEvent::~TimedEvent() {}