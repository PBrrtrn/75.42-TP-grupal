#include "itemspawnpoint.h"

ItemSpawnPoint::ItemSpawnPoint(QWidget* widget): ItemDraggable(widget)
{
    this->icon = ObjectList::textures.at(999);
    this->itemData = "SPAWNPOINT";
}
