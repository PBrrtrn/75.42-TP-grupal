#ifndef LANZA_COHETES_H
#define LANZA_COHETES_H

#include "arma.h"

class LanzaCohetes : public Arma {
    public:
        LanzaCohetes(std::string config);
        virtual ~LanzaCohetes() override;
};

#endif
