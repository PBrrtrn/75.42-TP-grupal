#ifndef PISTOLA_H
#define PISTOLA_H

#include "arma.h"

class Pistola : public Arma {
    public:
        Pistola();
        bool aimWeapon(float ort_dist, float target_dist) override;
        virtual ~Pistola() override;
};

#endif
