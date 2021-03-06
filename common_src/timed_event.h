#ifndef __TIMED_EVENT_H__
#define __TIMED_EVENT_H__

class TimedEvent {
    private:
        double timeout;
        double elapsed;
        double last_run_time;

        bool active;

    public:
        TimedEvent();

        virtual void activate(double timeout);
        virtual void deactivate();
        virtual bool update(double delta);

        virtual ~TimedEvent();
};

#endif