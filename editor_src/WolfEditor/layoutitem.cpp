#include "layoutitem.h"


LayoutItem::LayoutItem(MapServer* map,AppStatus& appStatus,float pos_x,float pos_y,std::string graphic,int scale,QGraphicsItem *parent)
    : QGraphicsLayoutItem(), QGraphicsItem(parent),
      m_pix(QPixmap(QLatin1String(graphic.c_str())).scaled(QSize(scale,scale))),
      map(map),
      appStatus(appStatus)
{
    this->hasItem = false;
    //this->map = map;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->scale = scale;
    setGraphicsItem(this);
    if (this->map->getGridValue(this->pos_x, this->pos_y) == 0)
        setAcceptDrops(true);

    for (auto& it: this->map->getItems()) {
        if (it->getPosition().getXCoordinate() == this->pos_x && it->getPosition().getYCoordinate() == this->pos_y){
            std::string texture = ObjectList::textures.at(it->getType());
            m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));
            this->hasItem = true;
        }
    }

    for (auto& it: this->map->getRespawnPoints()) {
        if (it.getPosition().getXCoordinate() == this->pos_x && it.getPosition().getYCoordinate() == this->pos_y){
            std::string texture = ObjectList::textures.at(999);
            m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));
            this->hasItem = true;
        }
    }


}

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


void LayoutItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    this->map->setGridValue(this->pos_x, this->pos_y,this->appStatus.getCurrentWallIndex());

    std::string texture = TextureList::textures.at(this->map->getGridValue(this->pos_x, this->pos_y));

	if (this->appStatus.getCurrentWallIndex() == 0){
		int i = 0;
        for (auto& it: this->map->getItems()) {
			//Vector pos(it->getPosition().getXCoordinate(),it->getPosition().getYCoordinate());
            if (it->getPosition().getXCoordinate() == this->pos_x && it->getPosition().getYCoordinate() == this->pos_y){
				this->map->eraseItemAt(i);
				break;
            }
			i++;
        }	
        
		i = 0;
        for (auto& it: this->map->getRespawnPoints()) {
			//Vector pos(it->getPosition().getXCoordinate(),it->getPosition().getYCoordinate());
            if (it.getPosition().getXCoordinate() == this->pos_x && it.getPosition().getYCoordinate() == this->pos_y){
				this->map->eraseSpawnPointAt(i);
				break;
            }
			i++;
        }	        
        	
	}

    m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));
    if (this->map->getGridValue(this->pos_x, this->pos_y) == 0){
        setAcceptDrops(true);
    }
    else {
        setAcceptDrops(false);
    }



    this->update();
}

void LayoutItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{

    if (!this->hasItem){
        event->acceptProposedAction();
    }
}

void LayoutItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if (!this->hasItem){

        EditorItemSerializer factory;
        ItemSerializer serializer;

        if (event->mimeData()->text() == "SPAWNPOINT")
        {
            SpawnPoint sp(Vector(this->pos_x,this->pos_y),Vector(1,0));
            this->map->insertSpawnPoint(sp);
        } else  {
            this->map->insertItem(factory.getItem(this->pos_x,this->pos_y,event->mimeData()->text().toUtf8().constData()));
        }
        this->hasItem = true;

        for (auto& it: this->map->getItems()) {
            if (it->getPosition().getXCoordinate() == this->pos_x && it->getPosition().getYCoordinate() == this->pos_y){
                std::string texture = ObjectList::textures.at(it->getType());
                m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));
            }
        }

        for (auto& it: this->map->getRespawnPoints()) {
            if (it.getPosition().getXCoordinate() == this->pos_x && it.getPosition().getYCoordinate() == this->pos_y){
                std::string texture = ObjectList::textures.at(999);
                m_pix = QPixmap(QLatin1String(texture.c_str())).scaled(QSize(this->scale,this->scale));
            }
        }

        this->update();
        event->acceptProposedAction();
    }
}
