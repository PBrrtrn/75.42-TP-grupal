#ifndef __ITEM_SERIALIZER_H_
#define __ITEM_SERIALIZER_H_

#include "item.h"
#include <sstream>
#include "bullets.h"
#include "food.h"

class ItemSerializer {
    public:
        ItemSerializer();
        Item deserialize(const std::string& serializedItem);
        std::string serialize(Item& item);
        ~ItemSerializer();
};

#endif

/*

	bool canBePicked;
	int timeToRespawn;
	int amount;
	Vector pos;
	bool respawns;
	bool isDecoration;
	bool has_volume;
*/
