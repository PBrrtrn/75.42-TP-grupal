#include "itemtable.h"

ItemTable::ItemTable(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_TABLE);
    this->itemData = "TABLE";
}

