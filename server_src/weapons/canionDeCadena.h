#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H

#include "arma.h"

class CanionDeCadena : public Arma {
    public:
        CanionDeCadena();
        bool aimWeapon(float ort_dist, float target_dist) override;
        virtual ~CanionDeCadena() override;
};

#endif
