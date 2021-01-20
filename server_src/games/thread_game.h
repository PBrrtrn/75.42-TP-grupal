#ifndef THREAD_GAME_H
#define THREAD_GAME_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>

#include "../communication/thread_client.h"
#include "../../common_src/thread.h"
#include "../../common_src/socket.h"
#include "game_status.h"

#include "../actions/action.h"
#include "../actions/move_right.h"
#include "../actions/move_left.h"
#include "../actions/move_backward.h"
#include "../actions/move_forward.h"
#include "../actions/shoot.h"

#include <unistd.h>  //removeme

class ThreadGame: public Thread {
        int id;
        BlockingQueue<Message>* messages;
        GameStatus gameStatus;
        std::unordered_map<int,ThreadClient*> clients;
        MoveForward move_forward;
        MoveLeft move_left;
        MoveRight move_right;
        MoveBackward move_backward;
        Shoot shoot;
        
        std::unordered_map<int, BlockingQueue<GameStatus>*> out_queues;
        
        bool keep_running;
        
        void checkNews();
        
        void expelClient(int id);

    public:
        ThreadGame(int gameId, BlockingQueue<Message>* m);
        virtual void run() override;
        void addClient(ThreadClient* client, int id);
        void tryMoveForward(int id);
        void tryMoveBackward(int id);
        void tryMoveLeft(int id);
        void tryMoveRight(int id);
        void tryShoot(int id);
        GameStatus getGameStatus();
        
        void sendGameUpdates();
        
        virtual ~ThreadGame() override;
};

#endif
