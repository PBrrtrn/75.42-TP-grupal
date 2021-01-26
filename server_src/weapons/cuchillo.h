#ifndef CUCHILLO_H
#define CUCHILLO_H

#include "arma.h"

class Cuchillo : public Arma {
    public:
        Cuchillo(std::string config);
        virtual ~Cuchillo() override;
};

#endif
