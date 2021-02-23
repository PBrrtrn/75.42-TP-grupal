#include "itemblood.h"

ItemBlood::ItemBlood(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemblood.png";
    this->itemData = "BLOOD";
}

