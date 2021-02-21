#include "layoutitem.h"


#include <QGradient>
#include <QPainter>
#include <QMessageBox>

//! [0]
LayoutItem::LayoutItem(Map& map,AppStatus& appStatus,int pos_x,int pos_y,std::string graphic,int scale,QGraphicsItem *parent)
    : QGraphicsLayoutItem(), QGraphicsItem(parent),
      m_pix(QPixmap(QLatin1String(graphic.c_str())).scaled(QSize(scale,scale))),
      map(map),
      appStatus(appStatus)
{
    this->map = map;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    setGraphicsItem(this);

}
//! [0]

//! [1]
void LayoutItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QRectF frame(QPointF(0, 0), geometry().size());
    const QSize pmSize = m_pix.size();
    QGradientStops stops;

    QPointF pixpos = frame.center() - (QPointF(pmSize.width(), pmSize.height()) / 2);
    painter->drawPixmap(pixpos, m_pix);
}
QRectF LayoutItem::boundingRect() const
{
    return QRectF(QPointF(0, 0), geometry().size());
}

void LayoutItem::setGeometry(const QRectF &geom)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(geom);
    setPos(geom.topLeft());
}

QSizeF LayoutItem::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    switch (which) {
    case Qt::MinimumSize:
        return m_pix.size()/2;
        break;
    case Qt::PreferredSize:
        // Do not allow a size smaller than the pixmap with two frames around it.
        return m_pix.size();// + QSize(1, 1);
        break;
    case Qt::MaximumSize:
        return QSizeF(1000,1000);
    default:
        break;
    }
    return constraint;
}
//! [5]

void LayoutItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    this->map.setGridValue(this->pos_x, this->pos_y,this->appStatus.getCurrentWallIndex());

    std::string texture = TextureList::textures.at(this->map.getGridValue(this->pos_x, this->pos_y));

    m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));

    this->update();
}


