#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H

#include "arma.h"

class CanionDeCadena : public Arma {
    public:
        CanionDeCadena();
        bool aimWeapon(float target_angle, float shooter_angle, float target_distance) override;
        virtual ~CanionDeCadena() override;
};

#endif
