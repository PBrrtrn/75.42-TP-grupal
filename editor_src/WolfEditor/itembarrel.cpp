#include "itembarrel.h"

ItemBarrel::ItemBarrel(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itembarrel.png";
    this->itemData = "BARREL";
}

