#ifndef THREAD_GAME_H
#define THREAD_GAME_H

#include <stdio.h>
#include <string.h>
#include <list>
#include <atomic>
#include <iostream>
#include<stdlib.h>
#include<time.h>

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
#include "../../common_src/LobbyStatusData.h"

#include "client_game_status.h"

class ThreadGame: public Thread {
        int id; /*numero de partida*/
        int map_id; /*id del mapa de la partida*/
        LobbyStatus& lobbyStatus;
        //LobbyStatusData lobbyData; TODO
        BlockingQueue<Message>* messages;
        std::unordered_map<int, BlockingQueue<Message>*> out_queues;

        /*clave: id game, value: lista de juegos activos en servidor*/
        std::unordered_map<int, GameListItem >& gameList;
        //TODO ver optimizacion --> ver si puede solo tener referencia a GameListItem

        /*clave: id del cliente, value: th cliente*/
        /*diccionario de clientes en partida*/
        std::unordered_map<int,ThreadClient*> clients;
        
        std::unordered_map<int,ClientGameStatus*> clientGameStatuses;
        
        GameStatus gameStatus;

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
        
        std::atomic<bool>start_running;
        std::atomic<bool>keep_running;
        std::atomic<bool>is_dead;
        int remaining_time;
        int waiting_time_to_start;
        

        /**
         * @brief Hace un pop de la cola bloqueante
         * para recibir un mensaje y hacer lo que corresponda
         */
        void checkNews();

        /**
         * @brief Metodos que llaman a los metodos 
         * correspondientes del game status
         */
		void checkPlayerPickups();
        void respawnItems();
		void checkPlayerBullets();   

        /**
         * @brief Envia las estadisticas
         * de la partida, una vez finalizada
         */
		void sendGameStatistics();

        /**
         * @brief Envia los datos actualizados
         * de la partida a sus jugadores.
         */
        void sendGameUpdates();

        /**
         * @brief Envia los datos del estado de 
         * espera de inicio del juego:
         * cantidad de jugadores que ingresaron y
         * tiempo restante para comenzar.
         */
        void sendLobbyStatus();

    public:
        ThreadGame(int gameId, BlockingQueue<Message>* m,
            std::unordered_map<int,GameListItem>& list, std::string map_location,
            int mapId, LobbyStatus& lobbyStatus);
        virtual void run() override;

        /**
         * @brief Agrega un nuevo jugador a la partida
         * si la misma todavia no comenzo y no supero
         * el maximo de jugadores permitidos
         * @param client: thread cliente
         * @param id: id asociado al cliente
         */
        bool addClient(ThreadClient* client, int id);

        /**
         * @brief Elimina un jugador de la partida
         * @param id: id del cliente a eliminar
         */
        void expelClient(int id);

        /**
         * @brief Metodos encargados de efectuar
         * las acciones solicitadas por el cliente 
         * en caso de ser validas
         */
        void tryMoveForward(int id);
        void tryMoveBackward(int id);
        void tryMoveLeft(int id);
        void tryMoveRight(int id);
        void tryShoot(int id);
        
        void changeMovementState(int playerId,MovementState state);
        void changeRotationState(int playerId,MovementState state);
        void updatePlayerPositions();
		void updatePlayerRotations();
		
		void changeWeaponAmetralladora(int id);
		void changeWeaponCanion(int id);
		void changeWeaponCuchillo(int id);
		void changeWeaponLanzacohetes(int id);
		void changeWeaponPistola(int id);
		
		void useDoor(int id);
		
		char getCurrentPlayers();
        char getMaxPlayers();
		void sendMapToClient(int clientId);

        bool isDead();
        void shutdown();
        
        virtual ~ThreadGame() override;
};

#endif
