#include "itemfood.h"

ItemFood::ItemFood(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemfood.png";
    this->itemData = "FOOD";
}

