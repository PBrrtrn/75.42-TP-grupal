#include "itembullets.h"

ItemBullets::ItemBullets(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itembullets.png";
    this->itemData = "BULLETS";
}

