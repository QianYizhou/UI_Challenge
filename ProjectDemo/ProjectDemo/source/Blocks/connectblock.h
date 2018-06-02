#ifndef CONNECTBLOCK_H
#define CONNECTBLOCK_H

#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsLineItem>


enum POS{
    LEFT,
    RIGHT,
    NEXT,
    COLLSION,
    NEXTSTEP
};



class ConnectBlock : public QGraphicsItem
{


public:

    ConnectBlock(int p);
    ~ConnectBlock();
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal course;
    qreal speed;
    short type;
    short attribute;
    QColor color;
    QPixmap *map;


    QPixmap *pixbtn;

    QPixmap *pixfill;

    QPoint point;

    QString title;

    QGraphicsPixmapItem block;

    QGraphicsLineItem *mynext;

    QString name;

    int pos;
    //QColor color;



protected:


    /*
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
    void dropEvent ( QGraphicsSceneDragDropEvent * event );
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    */


};



#endif // CONNECTBLOCK_H
