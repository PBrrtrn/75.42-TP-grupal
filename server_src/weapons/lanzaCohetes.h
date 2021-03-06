#ifndef LANZA_COHETES_H
#define LANZA_COHETES_H

#include "arma.h"

class LanzaCohetes : public Arma {
    public:
        LanzaCohetes();
        bool aimWeapon(float ort_dist, float target_dist) override;
        virtual ~LanzaCohetes() override;
};

#endif
