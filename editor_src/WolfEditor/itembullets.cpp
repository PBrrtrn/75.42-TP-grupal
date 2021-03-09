#include "itembullets.h"

ItemBullets::ItemBullets(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_BULLETS);
    this->itemData = "BULLETS";
}

