#ifndef ITEMDRAGGABLE_H
#define ITEMDRAGGABLE_H

#include <string>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include "../../server_src/items/ItemSerializer.h"
#include "../../server_src/games/SpawnPointSerializer.h"

class ItemDraggable : public QLabel
{
protected:
    std::string itemData;
    std::string icon;
private:
    void mousePressEvent(QMouseEvent *event);
public:
    ItemDraggable(QWidget* widget);
    virtual std::string getSerializedObject(int posX,int posY, bool respawns);
};

#endif // ITEMDRAGGABLE_H
