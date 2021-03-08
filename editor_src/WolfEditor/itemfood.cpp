#include "itemfood.h"

ItemFood::ItemFood(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_FOOD);
    this->itemData = "FOOD";
}

