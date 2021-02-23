#include "mapview.h"

MapView::MapView(QWidget* w) : QGraphicsView(w)
{
}

void MapView::dragEnterEvent(QDragEnterEvent *event)
{
    if (true){
        event->acceptProposedAction();
    }
}
