#include "itemtreasure.h"

ItemTreasure::ItemTreasure(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_TREASURE);
    this->itemData = "TREASURE";
}

