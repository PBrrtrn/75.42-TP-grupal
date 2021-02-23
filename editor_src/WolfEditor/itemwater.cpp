#include "itemwater.h"

ItemWater::ItemWater(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemwater.png";
    this->itemData = "WATER";
}

