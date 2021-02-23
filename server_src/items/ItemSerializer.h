#ifndef __ITEM_SERIALIZER_H_
#define __ITEM_SERIALIZER_H_

#include "item.h"
#include <sstream>
#include "bullets.h"
#include "food.h"
#include "water.h"
#include "treasure.h"
#include "table.h"
#include "medkit.h"
#include "key.h"
#include "corpse.h"
#include "bullets.h"
#include "blood.h"
#include "barrel.h"
#include "arma_ametralladora.h"
#include "arma_canion.h"
#include "arma_lanzacohetes.h"

class ItemSerializer {
    public:
        ItemSerializer();
        Item* deserialize(const std::string& serializedItem);
        std::string serialize(Item* item);
        ~ItemSerializer();
};

#endif
