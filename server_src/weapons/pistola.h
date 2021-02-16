#ifndef PISTOLA_H
#define PISTOLA_H

#include "arma.h"

class Pistola : public Arma {
    public:
        Pistola();
        bool aimWeapon(float target_angle, float shooter_angle, float target_distance) override;
        virtual ~Pistola() override;
};

#endif
