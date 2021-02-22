#include "itemfood.h"

ItemFood::ItemFood(QWidget* widget) : ItemDraggable(widget)
{
    this->icon = ":/images/itemfood.png";
}

std::string ItemFood::getSerializedObject(int posX,int posY, bool respawns){
    Food food(Vector(posX,posY),respawns);
    ItemSerializer serializer;
    return serializer.serialize(food);

}
