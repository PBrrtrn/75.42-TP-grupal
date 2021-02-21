/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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


