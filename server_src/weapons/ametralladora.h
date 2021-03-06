#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H

#include "arma.h"

class Ametralladora : public Arma {
    public:
        Ametralladora();
        bool aimWeapon(float ort_dist, float target_dist) override;
        virtual ~Ametralladora() override;
};

#endif
