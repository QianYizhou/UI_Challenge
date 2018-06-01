#include "blockicon.h"
#include <QDrag>
#include <QMimeData>
#include <QGridLayout>
#include <QToolBox>
#include <QApplication>
#include <QPainter>
#include <QtGui>
#include <QTextItem>
#include <QDebug>


#define ICON_OFFSET        60
extern float g_fScale;
extern qreal factor;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int ICON_SIZE_WIDTH;
extern int ICON_SIZE_HEIGHT;

GraphicsButtonItem::GraphicsButtonItem()
    :QGraphicsPixmapItem()
    ,QObject()
    ,m_isHover(false)
    ,m_isPressed(false)
{
    setAcceptHoverEvents(true);
}
GraphicsButtonItem::~GraphicsButtonItem()
{

}

QRectF GraphicsButtonItem::boundingRect()
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void GraphicsButtonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF l_rect = this->boundingRect();

    painter->drawPixmap(l_rect.x(), l_rect.y(), l_rect.width(), l_rect.height(), this->pixmap());
    if(m_isHover)
    {
        painter->fillRect(this->boundingRect(),QBrush(QColor(0,0,0,50)));
    }

    if(m_isPressed)
    {
        painter->fillRect(this->boundingRect(),QBrush(QColor(0,0,0,90)));
    }
}
void GraphicsButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHover = true;
    this->update();
    event->accept();
}
void GraphicsButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_isHover = false;
    this->update();
    event->accept();
}
void GraphicsButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    m_isPressed = true;
    this->update();
    emit pressed();
}
void GraphicsButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_isPressed = false;
    this->update();

    qDebug() << "pos: "<< event->pos() << " boundingRect: " << this->boundingRect();

    if(this->boundingRect().intersects(QRectF(0,0,event->pos().x(),event->pos().y())))
    {
        emit released();
    }
}

class BlockIconPrivate
{
public:
    BlockIconPrivate() {}
    QString myText;
    QPixmap m_iPixmap;
    QGraphicsTextItem* iconText;
    QPixmap m_ihoverbgPixmap;
    QPixmap m_ipressbgPixmap;
    QPixmap m_separatorPixmap;
    GraphicsButtonItem* m_trashBtn;
    QString m_Key;
    QElapsedTimer m_pressTimer;
    int m_pressCount;
    QVector2D m_PressPos;
    QTimer m_Timer;
};

BlockIcon::BlockIcon(int libtype, int id)
    :mylibtype(libtype)
    , m_IsEditMode(false)
    , d(new BlockIconPrivate())
{
    d->m_pressCount = 0;
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    ID = id;
    isselect = false;

    ishover = false;
    ispress = false;

    QPixmap p;
    p.load(":/ChartPC/res/windows/leftview/item_hover.png");
    setHoverBackgroundPixmap(p.scaled(172*g_fScaleX,44*g_fScaleY));

    p.load(":/ChartPC/res/windows/leftview/item_press.png");
    setPressBackgroundPixmap(p.scaled(172*g_fScaleX,44*g_fScaleY));

    d->iconText = NULL;
    d->m_trashBtn = NULL;
    connect(&(d->m_Timer),SIGNAL(timeout()),this,SLOT(ButtonClickedTimeout()));
    d->m_Timer.setSingleShot(true);
    d->m_Timer.setInterval(10);
}

BlockIcon::~BlockIcon()
{
    //qDebug() << "BlockIcon::~BlockIcon()" <<(int)this;
}

void BlockIcon::setMyText(const QString &text)
{
    d->myText = text;
#if defined Q_OS_LINUX_MY
    if(d->iconText == NULL)
    {
        d->iconText = new QGraphicsTextItem(this);//GraphicsIconText(this);
    }
    d->iconText->setTextWidth((190-48-20-10)*g_fScaleX);
    QString align = "center";
    QString html =QString("<div align='%1' top =50% >").arg(align)+getMyText()+QString("</div>");
    d->iconText->setHtml(html);
    d->iconText->setFont(MyFont::getfont(14));
    d->iconText->setDefaultTextColor(QColor(236,236,236));
    d->iconText->update();
    d->iconText->setPos((48+10)*g_fScaleX,(this->boundingRect().height() - d->iconText->boundingRect().height())/2);
#endif
}

QRectF BlockIcon::boundingRect() const
{
#if defined Q_OS_LINUX_MY
    return QRectF(0,0,198*g_fScaleX,50*g_fScaleY);
#endif

}

QPainterPath BlockIcon::shape() const
{
    QRectF rect = boundingRect();

    QPainterPath path;
    path.addRoundRect(rect, 5,5);
    return path;
}

QString BlockIcon::getMyText() const
{
    return d->myText;
}

void BlockIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(20, 0, d->m_iPixmap);

    if(m_IsEditMode)
    {
        QRectF rect = this->boundingRect();
        int l_imageHeight = d->m_separatorPixmap.height();
        painter->drawPixmap(rect.width() - rect.height() - 2,
                            (rect.height() -l_imageHeight) / 2 , d->m_separatorPixmap);
    }
    else
    {
        if(ishover)
            painter->drawPixmap(8, 4, d->m_ihoverbgPixmap);
        else {
            painter->fillRect(this->boundingRect(),QBrush(QColor(0,0,0,0)));
        }
        if(ispress)
            painter->drawPixmap(8, 4, d->m_ipressbgPixmap);
        else {
            painter->fillRect(this->boundingRect(),QBrush(QColor(0,0,0,0)));
        }
    }
}

void BlockIcon::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_IsEditMode)
    {
        return;
    }

    this->setTransformOriginPoint(this->boundingRect().center());
    this->setScale(1.05);
#if defined Q_OS_LINUX_MY
    ishover = true;
#endif
    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void BlockIcon::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_IsEditMode)
    {
        return;
    }

    this->setScale(1.0);
    isselect = false;
#if defined Q_OS_LINUX_MY
    ishover = false;
#endif
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

void BlockIcon::setPixmap(const QPixmap &pixmap)
{
    d->m_iPixmap = pixmap;
}
#if defined Q_OS_LINUX_MY
void BlockIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"BlockIcon::mousePressEvent"<<event->type() << "pos: " << event->pos();

    d->m_PressPos.setX(event->pos().x());
    d->m_PressPos.setY(event->pos().y());

    //d->m_pressTimer.start();
    ispress = true;
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

#define BlockIcon_Click (QEvent::User + 300)

void BlockIcon::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"BlockIcon::mouseReleaseEvent"<<event->type() << "pos: " << event->pos();

    if(ispress)
    {
        QVector2D l_endPos(event->pos().x(), event->pos().y());

        qDebug()<<"BlockIcon::m_pressTimer: " << d->m_pressTimer.elapsed() << " " << d->m_pressCount;

        if(++(d->m_pressCount) > 2 || d->m_pressCount == 1)
        {
            d->m_pressTimer.start();
            d->m_pressCount = 1;
        }

        if(d->m_pressTimer.elapsed() > 200 || d->m_pressTimer.elapsed() < 0)
        {
            d->m_pressTimer.start();
            d->m_pressCount = 1;
        }

        if(d->m_pressTimer.elapsed() <= 200 && d->m_pressCount >= 2 && d->m_PressPos.distanceToPoint(l_endPos) < 10)
        {
            //qApp->postEvent(this, new QEvent((QEvent::Type)BlockIcon_Click));
            qDebug() << "postEvent :: BlockIcon_Click";
            d->m_Timer.start();
        }
    }

    ispress = false;
    update();

    QGraphicsItem::mouseReleaseEvent(event);
}

void BlockIcon::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    d->m_Timer.start();
}

bool BlockIcon::event(QEvent *event)
{
    bool l_Result = true;

    if(event->type() == BlockIcon_Click)
    {
        event->ignore();
        emit buttonReleased(this);
    }
    else
    {
        l_Result = QObject::event(event);
    }

    return l_Result;
}

void BlockIcon::setHoverBackgroundPixmap(const QPixmap &pixmap)
{
    d->m_ihoverbgPixmap = pixmap;
}

void BlockIcon::setPressBackgroundPixmap(const QPixmap &pixmap)
{
    d->m_ipressbgPixmap = pixmap;
}
#endif

void BlockIcon::setEditMode(bool p_bEditMode)
{
    m_IsEditMode = p_bEditMode;
    if(m_IsEditMode)
    {
        if(d->m_separatorPixmap.isNull())
        {
            d->m_separatorPixmap.load(":/ChartPC/res/windows/leftview/skill_sepa.png");
        }
        if(d->m_trashBtn == NULL)
        {
            QPixmap l_trashPixmap(":/ChartPC/res/windows/leftview/skill_trash.png");
            d->m_trashBtn = new GraphicsButtonItem();
            d->m_trashBtn->setParentItem(this);
            d->m_trashBtn->setPixmap(l_trashPixmap);
            d->m_trashBtn->setToolTip(tr("删除"));
            connect(d->m_trashBtn,SIGNAL(released()),this,SLOT(onTrashButtonReleased()));

            QRectF l_rect = this->boundingRect();
            QPointF pos;

            int l_width = l_rect.height() - 30;
            int l_height = l_width * l_trashPixmap.height() / l_trashPixmap.width() ;

            pos.setX(l_rect.width() - l_width - 20);
            pos.setY((l_rect.height() - l_height) / 2);

            d->m_trashBtn->setPos(pos);

            d->m_trashBtn->setSize(QSize(l_width, l_height));
        }
    }

    if(d->m_trashBtn)
    {
        d->m_trashBtn->setVisible(m_IsEditMode);
    }

    this->update();
}

void BlockIcon::onTrashButtonReleased()
{
    emit trashButtonReleased(this);
}

void BlockIcon::setKey(QString p_Key)
{
    d->m_Key = p_Key;
}
QString& BlockIcon::getKey()
{
    return d->m_Key;
}

void BlockIcon::ButtonClickedTimeout()
{
    qDebug() << "emit BlockIcon_Click";
    emit buttonReleased(this);
}
