#ifndef AMETRALLADORA_H
#define AMETRALLADORA_H

#include "arma.h"

class Ametralladora : public Arma {
    public:
        Ametralladora(std::string config);
        virtual ~Ametralladora() override;
};

#endif
