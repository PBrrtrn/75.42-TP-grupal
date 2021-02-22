#ifndef ITEMFOOD_H
#define ITEMFOOD_H

#include "itemdraggable.h"
#include "../../server_src/items/food.h"

class ItemFood : public ItemDraggable
{
public:
    ItemFood(QWidget* widget);
    std::string getSerializedObject(int posX,int posY, bool respawns);
};

#endif // ITEMFOOD_H
