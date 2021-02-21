#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QObject>
#include <vector>
#include <unordered_map>
#include "Map.h"
#include "texture_list.h"
#include "appstatus.h"

//! [0]
class LayoutItem : public QGraphicsLayoutItem, public QGraphicsItem,public QObject
{
public:
    LayoutItem(Map& map,AppStatus& appStatus,int pos_x = 0,int pos_y = 0,std::string graphic = ":/images/block.png",int scale = 1,QGraphicsItem *parent = nullptr);

    // Inherited from QGraphicsLayoutItem
    void setGeometry(const QRectF &geom) override;
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;

    // Inherited from QGraphicsItem
    QRectF boundingRect() const override;
    //std::vector<std::vector<int>>& model_grid;
    std::unordered_map<int,std::string> texture_list;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;


    int pos_x;
    int pos_y;
    int scale;

private:
    QPixmap m_pix;
    Map& map;
    AppStatus& appStatus;

void mousePressEvent(QGraphicsSceneMouseEvent *event);


};
//! [0]

#endif // LAYOUTITEM_H
