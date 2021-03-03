#include "itemspawnpoint.h"

ItemSpawnPoint::ItemSpawnPoint(QWidget* widget): ItemDraggable(widget)
{
    this->icon = ":/images/itemspawn.png";
    this->itemData = "SPAWNPOINT";
}
