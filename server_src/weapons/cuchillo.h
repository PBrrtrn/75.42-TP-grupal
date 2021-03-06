#ifndef CUCHILLO_H
#define CUCHILLO_H

#include "arma.h"
#include <iostream>
#include <string>

class Cuchillo : public Arma {
    public:
        Cuchillo();
        bool aimWeapon(float ort_dist, float target_dist) override;
        virtual ~Cuchillo() override;
};

#endif
