#ifndef STATISTICS_H
#define STATISTICS_H

#include <unordered_map>

class Statistics {
    public:

        /*key: player_id, value: cantidad de enemigos matados*/
	    std::unordered_map<int, int> enemigos_matados;
        /*key: player_id, value: puntos por tesoro*/
        std::unordered_map<int,int> puntos_tesoro;
        /*key: player_id, value: balas disparadas*/
        std::unordered_map<int,int> balas_disparadas;

        Statistics();
        void addEnemyDead(int playerID);
        std::unordered_map<int, int>& getEnemysDead();
        void addPointsTreasure(int playerID, int amount);
        std::unordered_map<int, int>& getPointsGame();
        void addBulletShooted(int playerID);
        std::unordered_map<int, int>& getBulletsShot();
        ~Statistics();

};

#endif