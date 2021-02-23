#include "editoritemserializer.h"

#include <QDebug>

EditorItemSerializer::EditorItemSerializer()
{

}


Item* EditorItemSerializer::getItem(float x,float y,std::string type){

    ItemSerializer serializer;
    if (type == "FOOD") {
        return new Food(Vector(x,y),true);
    }
    if (type == "BULLETS") {
        return new Bullets(Vector(x,y),true);
    }
    if (type == "WATER") {
        return new Water(Vector(x,y),true);
    }
    if (type == "TREASURE") {
        return new Treasure(Vector(x,y),true);
    }
    if (type == "TABLE") {
        return new Table(Vector(x,y),true);
    }
    if (type == "MEDKIT") {
        return new Medkit(Vector(x,y),true);
    }
    if (type == "KEY") {
        return new Key(Vector(x,y),true);
    }
    if (type == "BLOOD") {
        return new Blood(Vector(x,y),true);
    }
    if (type == "BARREL") {
        return new Barrel(Vector(x,y),true);
    }
    if (type == "AMETRALLADORA") {
        return new ArmaAmetralladora(Vector(x,y),true);
    }
    if (type == "CANION") {
        return new ArmaCanion(Vector(x,y),true);
    }


}
