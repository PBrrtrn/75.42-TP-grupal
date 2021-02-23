#include "itemcanion.h"

ItemCanion::ItemCanion(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemcanion.png";
    this->itemData = "CANION";
}

