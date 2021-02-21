#ifndef ITEMDRAGGABLE_H
#define ITEMDRAGGABLE_H

#include <string>
#include <QLabel>
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

class ItemDraggable : public QLabel
{
protected:
    std::string itemData;
    std::string icon;
private:
    void mousePressEvent(QMouseEvent *event);
public:
    ItemDraggable(QWidget* widget);

};

#endif // ITEMDRAGGABLE_H
