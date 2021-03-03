#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QObject>
#include <QGradient>
#include <QPainter>
#include <QMessageBox>
#include <QMimeData>
#include <QGraphicsSceneDragDropEvent>
#include <vector>
#include <unordered_map>
#include "../../server_src/games/MapServer.h"
#include "texture_list.h"
#include "object_list.h"
#include "appstatus.h"
#include "editoritemserializer.h"

//! [0]
class LayoutItem : public QGraphicsLayoutItem, public QGraphicsItem,public QObject
{
public:
    LayoutItem(MapServer* map,AppStatus& appStatus,float pos_x = 0,float pos_y = 0,std::string graphic = ":/images/block.png",int scale = 1,QGraphicsItem *parent = nullptr);

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom) override;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const override;
    //std::vector<std::vector<int>>& model_grid;
    std::unordered_map<int,std::string> texture_list;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


    float pos_x;
    float pos_y;
    int scale;

private:
    QPixmap m_pix;
    MapServer* map;
    AppStatus& appStatus;
    bool hasItem;
void mousePressEvent(QGraphicsSceneMouseEvent *event);
void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
void dropEvent(QGraphicsSceneDragDropEvent *event) override ;

};
//! [0]

#endif // LAYOUTITEM_H
