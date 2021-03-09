#include "itemkey.h"

ItemKey::ItemKey(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_KEY);
    this->itemData = "KEY";
}

