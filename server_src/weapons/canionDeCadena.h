#ifndef CANION_DE_CADENA_H
#define CANION_DE_CADENA_H

#include "arma.h"

class CanionDeCadena : public Arma {
    public:
        CanionDeCadena(std::string config);
        virtual ~CanionDeCadena() override;
};

#endif
