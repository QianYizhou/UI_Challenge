#include "percubeline.h"
#include <QPainter>
#include <QDebug>
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
PerCubeLine::PerCubeLine(QPainterPath path,bool direction):QGraphicsPathItem (path)
  , pix(NULL)
{
    ispress = false;
    dir = direction;
}

void PerCubeLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QColor ccc = QColor(197,201,205);
    float s = g_fScaleX > g_fScaleY ? g_fScaleX : g_fScaleY;
    QPen penline(ccc, 12 * s, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(penline);
    if(ispress)
    {
        QPen penline1(QColor(197,201,205), 12 * s, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(penline1);
    }
    QPainterPath path = this->shape();
    painter->drawPath(path);
}

void PerCubeLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void PerCubeLine::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    ispress = true;
    update();
}
