#include "itemblood.h"

ItemBlood::ItemBlood(QWidget* widget) : ItemDraggable(widget)
{
    //this->icon = "../images/itemblood.png";
    this->icon = ObjectList::textures.at(TYPE_BLOOD);
    this->itemData = "BLOOD";
}

