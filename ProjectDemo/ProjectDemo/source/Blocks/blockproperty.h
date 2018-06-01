#ifndef BLOCKPROPERTY_H
#define BLOCKPROPERTY_H


#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QObject>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneHoverEvent>
#include <QPropertyAnimation>

class BlockProperty : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY (qreal rotation READ opacity WRITE setRotation)

    BlockProperty(QString iconfile, int id, QString text, bool type = false, QString Bubble = ":/res/ios/images/main_modulvalue.png");
    BlockProperty(const BlockProperty& other);
    BlockProperty* clone();
    ~BlockProperty();

    void setPos(const QPointF& pos);
    void setPos(qreal ax, qreal ay);

    //属性图标
    void setMyPixmap(const QString &pixmap);
    QString getMyPixmap() const;
    void setMyID(const int &id);
    int getMyID() const;

    QRectF boundingRect() const;
    QPainterPath shape() const;

public slots:


signals:


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString myIconFile;
    bool m_type;//if for while
    int myID;
    QString myText;
    QString myBubble;

    int myCharType;
    QGraphicsPixmapItem iconPixmap;
    QGraphicsPixmapItem bubblePixmap;
    QGraphicsTextItem textItem;
    QGraphicsTextItem fortextItem;
};



#endif // BLOCKPROPERTY_H
