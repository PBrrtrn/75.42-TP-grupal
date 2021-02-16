#ifndef LANZA_COHETES_H
#define LANZA_COHETES_H

#include "arma.h"

class LanzaCohetes : public Arma {
    public:
        LanzaCohetes();
        bool aimWeapon(float target_angle, float shooter_angle, float target_distance) override;
        virtual ~LanzaCohetes() override;
};

#endif
