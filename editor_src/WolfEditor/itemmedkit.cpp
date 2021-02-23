#include "itemmedkit.h"

ItemMedkit::ItemMedkit(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemmedkit.png";
    this->itemData = "MEDKIT";
}

