#ifndef BLOCKICON_H
#define BLOCKICON_H


#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QDragMoveEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QObject>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneHoverEvent>
#include <QPropertyAnimation>
#include "../define.h"
#include "../util/myfont.h"
#include <QVariant>
#include <QElapsedTimer>
#include <QVector2D>
#include <QScopedPointer>
#include <QPainter>
class GraphicsIconText : public QGraphicsTextItem
{
public:
    GraphicsIconText(QGraphicsItem *parent = Q_NULLPTR):QGraphicsTextItem(parent){}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
        painter->fillRect(this->boundingRect(),QBrush(QColor(255,0,0,50)));

        QGraphicsTextItem::paint(painter,option,widget);
    }

};
class GraphicsButtonItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GraphicsButtonItem();
    virtual ~GraphicsButtonItem();

    virtual QRectF boundingRect();

    inline void setSize(QSizeF p_size);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_isHover;
    bool m_isPressed;

    QSizeF m_size;



signals:
    void pressed();
    void released();

};

void GraphicsButtonItem::setSize(QSizeF p_size)
{
    m_size = p_size;
}

class BlockIconPrivate;
class BlockIcon : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Q_PROPERTY (qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY (qreal rotation READ opacity WRITE setRotation)
    void setMyText(const QString &text);
    QString getMyText() const;
    QRectF boundingRect() const;
    QPainterPath shape() const;

    BlockIcon(int libtype, int id);
    ~BlockIcon();

    int ID;
    QColor color;
    QString name;
    bool isselect;
    void setPixmap(const QPixmap& pixmap);
#if defined Q_OS_LINUX_MY
    void setHoverBackgroundPixmap(const QPixmap& pixmap);
    void setPressBackgroundPixmap(const QPixmap& pixmap);
#endif

    void setEditMode(bool p_bEditMode);

    void setKey(QString p_Key);
    QString& getKey();

signals:
    void trashButtonReleased(BlockIcon* p_sender);
    void buttonReleased(BlockIcon* p_sender);

public slots:
    void onTrashButtonReleased();
    void ButtonClickedTimeout();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
#if defined Q_OS_LINUX_MY
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
#endif

    bool event(QEvent *event);

private:
    int mylibtype;
    bool ishover;
    bool ispress;
    bool m_IsEditMode;

    QScopedPointer<BlockIconPrivate> d;

};

#endif // BLOCKICON_H
