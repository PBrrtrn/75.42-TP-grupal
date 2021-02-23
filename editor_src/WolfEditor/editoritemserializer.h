#ifndef EDITORITEMSERIALIZER_H
#define EDITORITEMSERIALIZER_H

#include "../../server_src/items/ItemSerializer.h"
#include "../../server_src/games/SpawnPointSerializer.h"

class EditorItemSerializer
{    
public:
    EditorItemSerializer();
    Item getItem(float x,float y,std::string type);
};

#endif // EDITORITEMSERIALIZER_H
