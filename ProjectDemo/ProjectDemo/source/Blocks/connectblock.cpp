#include "connectblock.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QScreen>
#include <QPainter>
#include <QStyleOption>
#include <math.h>
#include <QMenu>
#include <QDebug>
#include <QMimeData>
#include "../define.h"
#include "baseblock.h"
#include <QToolTip>

bool tipconnect = false;
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
int BLOCK_PER_DISTANCE = 80;
ConnectBlock::ConnectBlock(int p)
    : map(NULL)
    , pixbtn(NULL)
    , pixfill(NULL)
{
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    pos = p;

    QPixmap pixmap;
    int x = 0, y = 0;
    if(pos==LEFT)
    {
        pixmap.load(":/res/ios/images/left.png");
        pixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());

        {
            x = this->boundingRect().width() - pixmap.width() - 3*g_fScaleX;
            y = this->boundingRect().height()/2 - 51*g_fScaleY;
        }
    }
    else if(pos==RIGHT)
    {
        pixmap.load(":/res/ios/images/right.png");
        pixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());

        {
            x = this->boundingRect().width() - pixmap.width() - 6*g_fScaleX;
            y = this->boundingRect().height()/2 - 51*g_fScaleY;
        }

    }
    else if(pos==NEXT)
    {
        pixmap.load(":/res/ios/images/down.png");
        pixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());

        {
            x = (this->boundingRect().width() - pixmap.width()/QApplication::primaryScreen()->devicePixelRatio())/2;
            y = this->boundingRect().height()/2 - 40 * g_fScaleY;
        }
    }
    else if(pos == COLLSION)
    {
        //pixmap.load(":/res/ios/images/up.png");
        pixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());

        {
            x = (this->boundingRect().width() - pixmap.width()/QApplication::primaryScreen()->devicePixelRatio())/2;
            y = this->boundingRect().height()/2 - 40 * g_fScaleY;
        }
    }
    else if(pos==NEXTSTEP)
    {
        pixmap.load(":/res/ios/images/down.png");
        pixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());

        {
            x = this->boundingRect().width()/2 - 12*g_fScaleX;
            y = this->boundingRect().height()/2 - 40 * g_fScaleY;
        }
    }

    // 去掉有对话框覆盖后显示黑框
    QToolTip::hideText();
}

ConnectBlock::~ConnectBlock()
{
    qDebug("ConnectBlock::~ConnectBlock()");
    if(pixfill!=NULL){
        delete pixfill;
        pixfill = NULL;
    }
    if(pixbtn!=NULL){
        delete pixbtn;
        pixbtn = NULL;
    }
    if(map!=NULL){
        delete map;
        map = NULL;
    }
}

QRectF ConnectBlock::boundingRect()const
{
    if(pos==LEFT)
        return QRectF(0, 20 * g_fScaleY, 14, BLOCK_PER_DISTANCE + 20 * g_fScaleY);
    else if(pos==RIGHT)
        return QRectF(0, 20 * g_fScaleY, 14, BLOCK_PER_DISTANCE + 20 * g_fScaleY);
    else if(pos==NEXT)
        return QRectF(0, 0,92*g_fScaleX , BLOCK_PER_DISTANCE + 20 * g_fScaleY);
    else if(pos == COLLSION)
        return QRectF(0, 0,92*g_fScaleX , 25);
    else if(pos==NEXTSTEP)
        return QRectF(0, 0,45 , BLOCK_PER_DISTANCE + 20 * g_fScaleY);

    return QRectF();
}

void ConnectBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
//    return;
    painter->drawRect(this->boundingRect());
}
