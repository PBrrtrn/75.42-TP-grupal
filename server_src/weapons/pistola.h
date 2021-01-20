#ifndef PISTOLA_H
#define PISTOLA_H

#include "arma.h"

class Pistola : public Arma {
    public:
        Pistola(std::string config);
        virtual ~Pistola() override;
};

#endif //GAMESTATUS_H
