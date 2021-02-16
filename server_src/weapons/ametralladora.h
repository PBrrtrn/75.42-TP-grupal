#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H

#include "arma.h"

class Ametralladora : public Arma {
    public:
        Ametralladora();
        bool aimWeapon(float target_angle, float shooter_angle, float target_distance) override;
        virtual ~Ametralladora() override;
};

#endif
