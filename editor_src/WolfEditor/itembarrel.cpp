#include "itembarrel.h"

ItemBarrel::ItemBarrel(QWidget* widget) : ItemDraggable(widget)
{
    //this->icon = "../images/itembarrel.png";
    this->icon = ObjectList::textures.at(TYPE_BARREL);
    this->itemData = "BARREL";
}

