#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include <string>
#include <unordered_map>

namespace ObjectList {
static std::unordered_map<int,std::string> textures({{TYPE_BULLETS,"../images/itembullets.png"},
                                                     {TYPE_FOOD,"../images/itemfood.png"},
                                                     {TYPE_ARMA_CANION,"../images/itemcanion.png"},
                                                     {TYPE_ARMA_AMETRALLADORA,"../images/itemametralladora.png"},
                                                     {TYPE_KEY,"../images/itemkey.png"},
                                                     {TYPE_MEDKIT,"../images/itemmedkit.png"},
                                                     {TYPE_TREASURE,"../images/itemtreasure.png"},
                                                     {999,"../images/itemspawn.png"}
                                               });
}

#endif
