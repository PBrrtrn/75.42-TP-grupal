#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>
#include <QWidget>
#include <QMessageBox>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDropEvent>

class MapView : public QGraphicsView
{
public:
    MapView(QWidget* w);
private:
    void dragEnterEvent(QDragEnterEvent *event);
    //void dropEvent(QDropEvent *event);
};

#endif // MAPVIEW_H
