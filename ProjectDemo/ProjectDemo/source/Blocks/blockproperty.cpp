#include "blockproperty.h"
#include <QDebug>
#include <QMimeData>
#include <QGridLayout>
#include <QToolBox>
#include <QApplication>
#include <QPainter>
#include <QtGui>
#include <QTextItem>
#include "../define.h"
#include "../util/myfont.h"

extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
int ICON_WIDTH = 54;
int ICON_HEIGHT = 46;
int BUBBLE_WIDTH = 88;
int BUBBLE3_WIDTH = 168;
int BUBBLE2_WIDTH = 128;
int BUBBLE_HEIGHT = 56;
qreal CHAR_WIDTH = 0;

BlockProperty::BlockProperty(QString iconfile, int id, QString text, bool type, QString Bubble):
    myIconFile(iconfile)
  , m_type(type)
  , myID(id)
  , myText(text)
  , myBubble(Bubble)
{
    setCacheMode(DeviceCoordinateCache);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setAcceptHoverEvents(true);

    myCharType = 1;

}

BlockProperty::BlockProperty(const BlockProperty &other)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    setCacheMode(DeviceCoordinateCache);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setAcceptHoverEvents(true);

    this->myCharType = other.myCharType;
    myIconFile = other.myIconFile;
    m_type = other.m_type;
    myID = other.myID;
    myText = other.myText;
    myBubble = other.myBubble;
}

BlockProperty* BlockProperty::clone()
{
    BlockProperty* p = new BlockProperty(*this);
    return p;
}

BlockProperty::~BlockProperty()
{
    qDebug() << "BlockProperty::~BlockProperty";
}

void BlockProperty::setPos(const QPointF &pos)
{
    QPointF temp = pos;
    temp.setX(temp.x() * g_fScale);
    temp.setY(temp.y() * g_fScale);
    QGraphicsItem::setPos(temp);
}

void BlockProperty::setPos(qreal ax, qreal ay)
{
    QGraphicsItem::setPos(ax * g_fScale, ay * g_fScale);
}

void BlockProperty::setMyPixmap(const QString &pixmap)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    myIconFile = pixmap;
    bool g_bIpad = false;
    if(false == g_bIpad){
        if(m_type)
        {
            QPixmap pix(myIconFile);
            pix = pix.scaled(pix.size().width()*QApplication::primaryScreen()->devicePixelRatio()*ss,
                             pix.size().height()*QApplication::primaryScreen()->devicePixelRatio()*ss);
            pix.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());
            iconPixmap.setPixmap(pix);
            iconPixmap.setParentItem(this);
            iconPixmap.setPos(0.0  * g_fScaleX, 0.0 * g_fScaleY);
        }
        else
        {
            iconPixmap.setPixmap(QPixmap(myIconFile));
        }
    }
    update();
}

QString BlockProperty::getMyPixmap() const
{
    return myIconFile;
}

void BlockProperty::setMyID(const int &id)
{
    myID = id;
}

int BlockProperty::getMyID() const
{
    return myID;
}

QRectF BlockProperty::boundingRect() const
{
#if defined Q_OS_LINUX_MY
    QRect rect;
    if(m_type){
        rect.setRect(0*g_fScale,0*g_fScale,114*g_fScale,79*g_fScale);

    }else{
        if(myBubble.contains("2")){
            rect.setRect(0*g_fScale,0*g_fScale,BUBBLE2_WIDTH*g_fScale,130*g_fScale);
        }else if(myBubble.contains("3")){
            rect.setRect(0*g_fScale,0*g_fScale,BUBBLE3_WIDTH*g_fScale,130*g_fScale);
        }else{
            rect.setRect(0*g_fScale,0*g_fScale,BUBBLE_WIDTH*g_fScale,130*g_fScale);
        }
    }
    return QRectF(0,0,rect.width(),rect.height());
#endif
}

QPainterPath BlockProperty::shape() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRoundRect(rect, 5,5);
    return path;
}

void BlockProperty::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qDebug("BlockProperty::paint");
    this->parentItem()->update();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

}
