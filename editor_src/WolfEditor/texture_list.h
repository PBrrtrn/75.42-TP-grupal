#ifndef __TEXTURE_LIST_H__
#define __TEXTURE_LIST_H__

#include <string>
#include <unordered_map>

namespace TextureList {
static std::unordered_map<int,std::string> textures({{0,"../images/empty.png"},
                                                {1,"../images/bluestone.png"},
                                                {2,"../images/colorstone.png"},
                                                {3,"../images/eagle.png"},
                                                {4,"../images/greystone.png"}
                                               });
}

#endif
