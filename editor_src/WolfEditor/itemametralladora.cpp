#include "itemametralladora.h"

ItemAmetralladora::ItemAmetralladora(QWidget* widget) : ItemDraggable(widget)
{
    //this->icon = "../images/itemametralladora.png";
    this->icon = ObjectList::textures.at(TYPE_ARMA_AMETRALLADORA);
    this->itemData = "AMETRALLADORA";
}

