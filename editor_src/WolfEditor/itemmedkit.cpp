#include "itemmedkit.h"

ItemMedkit::ItemMedkit(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_MEDKIT);
    this->itemData = "MEDKIT";
}

