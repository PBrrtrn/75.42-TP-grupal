#ifndef THREAD_GAME_H
#define THREAD_GAME_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>

#include "../communication/thread_client.h"
#include "../../common_src/Thread.h"
/////#include "../../common_src/socket.h"
#include "game_status.h"

#include "../actions/action.h"
#include "../actions/move_right.h"
#include "../actions/move_left.h"
#include "../actions/move_backward.h"
#include "../actions/move_forward.h"
#include "../actions/shoot.h"
#include "../actions/change_weapon_cuchillo.h"
#include "../actions/change_weapon_ametralladora.h"
#include "../actions/change_weapon_pistola.h"
#include "../actions/change_weapon_canion.h"
#include "../actions/change_weapon_lanzacohetes.h"
#include "../actions/use_door.h"

#include "../../common_src/GameListItem.h"

class ThreadGame: public Thread {
        int id;
        BlockingQueue<Message>* messages;
        std::unordered_map<int,GameListItem>& gameList;
        GameStatus gameStatus;
        std::unordered_map<int,ThreadClient*> clients;
        MoveForward move_forward;
        MoveLeft move_left;
        MoveRight move_right;
        MoveBackward move_backward;
        Shoot shoot;
        ChangeWeaponCuchillo change_cuchillo;
        ChangeWeaponAmetralladora change_ametralladora;
        ChangeWeaponCanion change_canion;
        ChangeWeaponPistola change_pistola;
        ChangeWeaponLanzaCohetes change_lanzacohetes;

        UseDoor use_door;
        
        std::unordered_map<int, BlockingQueue<GameStatus>*> out_queues;
        
        bool start_running;
        bool keep_running;
        int remaining_time;
        int waiting_time_to_start;
        
        void checkNews();
        
        void expelClient(int id);
        
		void checkPlayerPickups();

		void sendGameStatistics();   

    public:
        ThreadGame(int gameId, BlockingQueue<Message>* m,std::unordered_map<int,GameListItem>& list);
        virtual void run() override;
        bool addClient(ThreadClient* client, int id);
        void tryMoveForward(int id);
        void tryMoveBackward(int id);
        void tryMoveLeft(int id);
        void tryMoveRight(int id);
        void tryShoot(int id);
        GameStatus getGameStatus();
        
        void sendGameUpdates();
        
        void respawnItems();
		void checkPlayerBullets();   
		
		void changeWeaponAmetralladora(int id);
		void changeWeaponCanion(int id);
		void changeWeaponCuchillo(int id);
		void changeWeaponLanzacohetes(int id);
		void changeWeaponPistola(int id);
		
		void useDoor(int id);
		
		char getMapId();
		char getCurrentPlayers();
        char getMaxPlayers();
        
        virtual ~ThreadGame() override;
};

#endif
