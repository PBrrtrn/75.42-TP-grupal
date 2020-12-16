#ifndef THREAD_DRAW_H
#define THREAD_DRAW_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include "../Thread.h"
#include "../GameStatus.h"
#include "Drawer.h"

class ThreadDraw: public Thread {
    std::atomic<bool>running{true};
    GameStatus& gStatus;
    Drawer& drawer;
    int clientID;

    public:
    ThreadDraw(GameStatus& gStatus, Drawer& drawer, int clientID);
    virtual void run() override;
    void stop();
    virtual ~ThreadDraw() override;
};

#endif
