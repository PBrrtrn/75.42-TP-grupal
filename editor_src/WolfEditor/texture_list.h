#ifndef __TEXTURE_LIST_H__
#define __TEXTURE_LIST_H__

#include <string>
#include <unordered_map>

namespace TextureList {
static std::unordered_map<int,std::string> textures({{0,"../images/empty.png"},
                                                {1,"../images/wood.png"},
						{2,"../images/bluestone.png"},
                                                {3,"../images/colorstone.png"},
                                                {4,"../images/eagle.png"},
                                                {5,"../images/greystone.png"}
                                               });
}

#endif
