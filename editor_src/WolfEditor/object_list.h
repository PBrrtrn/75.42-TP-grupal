#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

#include <string>
#include <unordered_map>

namespace ObjectList {
static std::unordered_map<int,std::string> textures({{1,"./images/itembullets.png"},
                                                     {2,"./images/itemfood.png"},
                                                     {3,"./images/itemcanion.png"},
                                                     {4,"./images/itemametralladora.png"},
                                                     {9,"./images/itemkey.png"},
                                                     {10,"./images/itemmedkit.png"},
                                                     {12,"./images/itemtreasure.png"},
                                                     {999,"./images/itemspawn.png"}
                                               });
}

#endif
