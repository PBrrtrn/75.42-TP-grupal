#include "itemkey.h"

ItemKey::ItemKey(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemkey.png";
    this->itemData = "KEY";
}

