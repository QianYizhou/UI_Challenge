#ifndef PERCUBELINE_H
#define PERCUBELINE_H

#include <QGraphicsPathItem>
#include <QPen>
#include <QDebug>
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;

class PerCubeLine : public QGraphicsPathItem
{
    //Q_OBJECT
public:
    PerCubeLine(QPainterPath  path,bool direction = false );

    ~PerCubeLine(){
        qDebug()<<"delete myself PerCubeLine!!!!!!!!!";
        if(pix!=NULL){
            delete pix;
            pix = NULL;
        }
    }

    QPainterPath thispath;

    QPixmap *pix;

    QPixmap pixdraw[10];
    bool ispress;
signals:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    bool dir;
private slots:

};

#endif // PERCUBELINE_H
