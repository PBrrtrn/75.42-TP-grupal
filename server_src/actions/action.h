#ifndef ACTION_H
#define ACTION_H

#include "../../common_src/Vector.h"
#include "../games/game_status.h"

class Action {
protected:
    int step;
    int rotation_left;
    int rotation_right;
    
public:
    explicit Action();

    /**
     * @brief Efectua la accion solicitada por el jugador
     * en caso de ser valida
     */
    virtual void tryAction(GameStatus& gs, int clientID);

    /**
     * @brief Analiza si la posicion hacia la que quiere moverse
     * el jugador resulta ser una colision contra una pared
     * u otro obstaculo. Devuelve true si es una colision (movimiento
     * invalido), o false en caso de que no haya colision (movimiento
     * valido)
     * @param clientID: id del cliente que quiere moverse
     * @param next_position: posicion hacia la que quiere moverse
     * @param gs: status actual del juego
     */
    bool is_colision(int clientID, Vector& next_position, GameStatus& gs);
    ~Action();
};

#endif
