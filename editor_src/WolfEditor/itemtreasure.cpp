#include "itemtreasure.h"

ItemTreasure::ItemTreasure(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemtreasure.png";
    this->itemData = "TREASURE";
}

