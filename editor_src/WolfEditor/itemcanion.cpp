#include "itemcanion.h"

ItemCanion::ItemCanion(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(TYPE_ARMA_CANION);
    this->itemData = "CANION";
}

