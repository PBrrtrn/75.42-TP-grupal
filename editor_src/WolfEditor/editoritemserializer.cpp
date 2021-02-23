#include "editoritemserializer.h"

#include <QDebug>

EditorItemSerializer::EditorItemSerializer()
{

}


Item EditorItemSerializer::getItem(float x,float y,std::string type){

    ItemSerializer serializer;
    if (type == "FOOD") {
        Food item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "BULLETS") {
        Bullets item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "WATER") {
        Water item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "TREASURE") {
        Treasure item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "TABLE") {
        Table item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "MEDKIT") {
        Medkit item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "KEY") {
        Key item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "BLOOD") {
        Blood item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "BARREL") {
        Barrel item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "AMETRALLADORA") {
        ArmaAmetralladora item(Vector(x,y),true);
        return std::move(item);
    }
    if (type == "CANION") {
        ArmaCanion item(Vector(x,y),true);
        return std::move(item);
    }


}
