#ifndef THREAD_GAME_H
#define THREAD_GAME_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>

#include "thread_client.h"
#include "../common_src/socket.h"
#include "../communication/thread_client.h"
#include "game_status.h"

#include "action.h"
#include "move_right.h"
#include "move_left.h"
#include "move_backward.h"
#include "move_forward.h"

class ThreadGame: public Thread {
    GameStatus gameStatus;
    std::vector<ThreadClient&> clients;
    Map map;
    MoveForward move_forward;
	MoveLeft move_left;
	MoveRight move_right;
	MoveBackward move_backward;

    public:
    ThreadGame();
    virtual void run() override;
    void addClient(ThreadClient& client);
    void tryMoveForward(int id);
    void tryMoveBackward(int id);
    void tryMoveLeft(int id);
    void tryMoveRight(int id);
    void tryShoot(int id);
    virtual ~ThreadGame() override;
};

#endif
