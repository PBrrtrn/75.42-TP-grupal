#include "itemtable.h"

ItemTable::ItemTable(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemtable.png";
    this->itemData = "TABLE";
}

