#ifndef CUCHILLO_H
#define CUCHILLO_H

#include "arma.h"
#include <iostream>

class Cuchillo : public Arma {
    public:
        Cuchillo();
        bool aimWeapon(float target_angle, float shooter_angle, float target_distance) override;
        virtual ~Cuchillo() override;
};

#endif
