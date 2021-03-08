#include "itemwater.h"

ItemWater::ItemWater(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_WATER);
    this->itemData = "WATER";
}

