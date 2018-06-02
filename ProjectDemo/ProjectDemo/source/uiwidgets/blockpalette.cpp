#include "blockpalette.h"

#include <algorithm>
#include <QDebug>
#include <QScrollBar>
#include <QtAlgorithms>
#include "../Blocks/baseblock.h"
#include "../Blocks/blockicon.h"
#include "../util/qwidgetutils.h"
#include "../util/commonhelper.h"
#include "../define.h"
#include "../Blocks/blockbuilder.h"
#include "projectview.h"
extern ProjectView* m_pCurrentProjectView;
extern float g_fScale;
extern qreal factor;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int ICON_SIZE_WIDTH;
extern int ICON_SIZE_HEIGHT;
static const int l_marginY = 55;
int CurrentSelect = 0;
BaseBlock *FirstBlock = NULL;
extern BaseBlock *CurrentBlock;
typedef BlockPalette::ItemPropertyList_t ItemPropertyList_t;
typedef BlockPalette::ItemProperty_t ItemProperty_t;
BlockCatalog::BlockCatalog(int p_catalogId, QString p_catalogName)
    :QGraphicsObject()
    , m_catalogName(p_catalogName)
    , m_catalogId(p_catalogId)
    , m_pen(QColor::fromRgb(15,68,165))
{
    m_font.setPixelSize(18);
    m_font.setBold(true);

    m_pen.setWidth(2);

}


QRectF BlockCatalog::boundingRect() const
{
    static const QRectF rect(0,0, 400, 40);
    return rect;
}
void BlockCatalog::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(m_font);
    painter->setPen(m_pen);

    painter->drawText(10,20, m_catalogName);

    painter->drawLine(QPointF(10, 30), QPointF(100, 30));
}

BlockPalette::BlockPalette(QWidget *parent)
    : QGraphicsView(parent)
//    , m_pMainWidget((MainWidget*)parent)
{
    this->setScene(new QGraphicsScene());
    this->scene()->setSceneRect(0,0, 100, 1000);
    this->setObjectName("BlockPalette");

    setDragMode(QGraphicsView::ScrollHandDrag);
    viewport()->setCursor(QCursor(Qt::ArrowCursor));

    verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    horizontalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);

    setStyleSheet(scrollBarStyleSheet());

    viewport()->setStyleSheet("QWidget {background-image: url(:/block_palette/res/images/block_palette/bg.png);}");

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)),
            this, SLOT(onVerticalScrollBarValueChanged(int)));

    loadBlocks();

    isPress = false;

}

BlockPalette::~BlockPalette()
{

}

QString BlockPalette::scrollBarStyleSheet()
{
    QString l_styleSheet;

    l_styleSheet.append("QWidget#BlockPalette {background:rgba(0,0,0,30%);}"); //background-image: url(:/block_palette/res/images/block_palette/bg.png);
    l_styleSheet.append("QScrollBar{background:transparent;}");
    l_styleSheet.append("QScrollBar:horizontal {border: none;background: rgba(0,0,0,1%); height: 15px;margin: 4px 10px 4px 10px; left:100px;right:100px}");
    l_styleSheet.append("QScrollBar:vertical {border: none;background: rgba(0,0,0,1%); width: 15px;margin: 10px 4px 10px 4px;}");
    l_styleSheet.append("QScrollBar::handle { background: rgb(113,216,217);min-width: 10px; max-width: 15px;} ");
    l_styleSheet.append("QScrollBar::handle:vertical{width:8px;background:rgba(113,216,217,25%);border-radius:2px;min-height:20;}");
    l_styleSheet.append("QScrollBar::handle:vertical:hover{width:8px;background:rgba(113,216,217,50%);border-radius:2px;min-height:20;}");
    l_styleSheet.append("QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical, QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {background:rgba(255,255,255,50%);}");

    l_styleSheet.append("QScrollBar::add-line:horizontal { border: none;background: transparent;width: 10px;subcontrol-position: right;subcontrol-origin: margin;}");
    l_styleSheet.append("QScrollBar::sub-line:horizontal {border: none;background: transparent;width: 10px;subcontrol-position: left; subcontrol-origin: margin;}");


    l_styleSheet.append("QScrollBar::add-line:vertical { border: none;background: transparent;height: 10px;subcontrol-position: bottom;subcontrol-origin: margin;}");
    l_styleSheet.append("QScrollBar::sub-line:vertical {border: none;background: transparent;height: 10px;subcontrol-position: top; subcontrol-origin: margin;}");


//    l_styleSheet.append("QScrollBar:left-arrow {border-image: url(:/block_palette/res/images/block_palette/ScrollBar/scroll_left.png);}");
//    l_styleSheet.append("QScrollBar:right-arrow {border-image: url(:/block_palette/res/images/block_palette/ScrollBar/scroll_right.png);}");
//    l_styleSheet.append("QScrollBar:up-arrow {border-image: url(:/block_palette/res/images/block_palette/ScrollBar/scroll_up.png);}");
//    l_styleSheet.append("QScrollBar:down-arrow {border-image: url(:/block_palette/res/images/block_palette/ScrollBar/scroll_down.png);}");

    return l_styleSheet;
}

void BlockPalette::loadBlocks()
{
    this->scene()->clear();
    m_catInfoList.clear();
    nextY = 0;
    //
    loadControlItem();
    loadSensorItem();
    loadCommandItem();


}

void BlockPalette::loadControlItem()
{
    ItemPropertyList_t itemList;

    {
        itemList.append(ItemProperty_t(BLOCK_MOVE,
                                       tr("移动"), ":/blockpalette/res/images/leftview/Controler/icon_up_f.png"));
    }
    {
        itemList.append(ItemProperty_t(BLOCK_GRAB,
                                       tr("抓取"), ":/blockpalette/res/images/leftview/Sensor/icon_grab.png"));
    }
    LoadItems(MODULELIB_CONTROLER, itemList);
}

void BlockPalette::loadSensorItem()
{
    ItemPropertyList_t itemList;
    {
        itemList.append(ItemProperty_t(BLOCK_POSITIONEXAMINE,
                                       tr("检测"), ":/blockpalette/res/images/leftview/Sensor/icon_encode.png"));
    }
    LoadItems(MODULELIB_SENSOR, itemList);
}

void BlockPalette::loadCommandItem()
{
    ItemPropertyList_t itemList;
    {
        itemList.append(ItemProperty_t(BLOCK_IF, tr("条件判断"), ":/blockpalette/res/images/leftview/Command/icon_if.png"));

        itemList.append(ItemProperty_t(BLOCK_FOR, tr("多次循环"), ":/blockpalette/res/images/leftview/Command/icon_for.png"));

        itemList.append(ItemProperty_t(BLOCK_WHILE, tr("循环判断"), ":/blockpalette/res/images/leftview/Command/icon_while.png"));

        itemList.append(ItemProperty_t(BLOCK_BREAK, tr("中断"), ":/blockpalette/res/images/leftview/Command/icon_break.png"));

        itemList.append(ItemProperty_t(BLOCK_CONTINUE, tr("继续循环"), ":/blockpalette/res/images/leftview/Command/icon_continue.png"));

        itemList.append(ItemProperty_t(BLOCK_RETURN, tr("返回"), ":/blockpalette/res/images/leftview/Command/icon_return.png"));
    }
    LoadItems(MODULELIB_COMMAND, itemList);
}

void BlockPalette::LoadItems(int libType, ItemPropertyList_t& p_Items)
{
    QPixmap p;
    int ICON_START_X = 0;

    BlockIcon* block = NULL;
    for(int l_Index = 0; l_Index < p_Items.size(); l_Index++)
    {
        const ItemProperty_t& l_Item = p_Items.at(l_Index);

        block = new BlockIcon(libType, l_Item.m_Id);
        p.load(l_Item.m_Icon);
        block->setPos(ICON_START_X, nextY);
        block->setPixmap(p.scaled(48*g_fScaleX,48*g_fScaleY));
        block->setMyText(l_Item.m_Name);
        block->setKey(l_Item.m_Key);
        setLeftViewIconText(block,this->scene());

        this->scene()->addItem(block);
        nextY +=  (l_marginY+48*g_fScaleY+2);
    }
}

void BlockPalette::setLeftViewIconText(BlockIcon *block, QGraphicsScene *scene)
{
    qreal g_fScaleX;
    qreal g_fScaleY;
    g_fScaleX = ::g_fScaleX/factor;
    g_fScaleY = ::g_fScaleY/factor;

    QGraphicsPixmapItem* backItem = NULL;
    QPixmap pixmap;
    pixmap.load(":/blockpalette/res/images/leftview/item_separator.png");

    pixmap = pixmap.scaled(158*g_fScaleX,1*g_fScaleY);
    backItem = new QGraphicsPixmapItem(pixmap);
    backItem->setPos(block->x() + 14*g_fScaleX, block->y()+block->boundingRect().height());
    backItem->setZValue(-10);
    scene->addItem(backItem);
}

int BlockPalette::calculationOffset(int libType)
{
    int yoffset = 0;
    switch (libType) {
    case MODULELIB_CONTROLER:
        yoffset = 0;
        break;
    case MODULELIB_SENSOR:
        yoffset = (yoffset+48*g_fScaleY+2) * 2;
        break;
    case MODULELIB_COMMAND:
        yoffset = (yoffset+48*g_fScaleY+2) * 3;
        break;
    case MODULELIB_VAR:
        yoffset = (yoffset+48*g_fScaleY+2) * 9;
        break;
    default:
        break;
    }
    return yoffset;
}

void BlockPalette::addBlock(BaseBlock* b)
{

    b->setPos(QPointF(20, nextY));
    b->setFlag(QGraphicsItem::ItemIsMovable,false);

    this->scene()->addItem(b);
    nextY += b->boundingRect().height() + 24;

    this->scene()->setSceneRect(0,0, 100, nextY);
}

void BlockPalette::resizeEvent(QResizeEvent *event)
{
    sceneResize();
    QGraphicsView::resizeEvent(event);
}

void BlockPalette::sceneResize()
{
    int l_width = width();
    int l_height = nextY - m_LastCatHeight;
    l_height += qMax(height(), m_LastCatHeight);

    this->scene()->setSceneRect(0,0, l_width - 20, l_height);
}

void BlockPalette::onSelectedCatChanged(int p_Index)
{
    int y = 0;
    if(p_Index >= 0 && p_Index < m_catInfoList.size())
    {
        y = m_catInfoList[p_Index].m_startPointY;

        this->centerOn(width() / 2.0 - 10 , y + (height() / 2.0));
    }
}

void BlockPalette::onVerticalScrollBarValueChanged(int value)
{
    /*if(m_pMainWidget->dragBlock().isVisible())
    {
        Block* block = m_pMainWidget->dragBlock().m_hoverBlock;
        QPointF posF = block->pos();
        QPoint pos = this->mapFromScene(posF);

        if(pos.y() <= l_marginY + 10)
        {
            m_pMainWidget->dragBlock().hide();
        }
        else
        {
            pos = this->mapToGlobal(pos);
            m_pMainWidget->dragBlock().showHoverBlock(block, pos);
        }

    }*/

    emitCurrentCatChanged(value);

//    qDebug() << "p_scrollValue " << value;

}

void BlockPalette::emitCurrentCatChanged(int p_scrollValue)
{
    int index = 0;
    for( index = 0; index < m_catInfoList.size(); index++)
    {
        if( qAbs(m_catInfoList[index].m_startPointY - p_scrollValue) < 10 )
        {
            emit currentCatChanged(index);
            return;
        }
        else if( p_scrollValue > m_catInfoList[index].m_startPointY )
        {
            if( (index < m_catInfoList.size() - 1 && p_scrollValue < m_catInfoList[index + 1].m_startPointY))
            {
                emit currentCatChanged(index);
                return;
            }
        }
    }

    if(index == m_catInfoList.size())
    {
        emit currentCatChanged(index - 1);
    }
}
typedef QList<QGraphicsItem*>   ItemList_t;
typedef QList<BaseBlock*>       BlockList;

void BlockPalette::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    QGraphicsItem *item = NULL;
    BlockIcon *newitem = NULL;
    item = this->itemAt(event->pos());
    if(item!=NULL)
    {
        newitem = dynamic_cast<BlockIcon*>(item);
        if(newitem == NULL)
        {
            newitem = dynamic_cast<BlockIcon*>(item->parentItem());
        }
        if(newitem!=NULL)
        {
            if(FirstBlock!=NULL)
            {
                qDebug()<<"ccc ID = "<<CurrentSelect;
                if(FirstBlock->nextnode!=NULL){
                    FirstBlock->nextnode = NULL;
                }

                delete FirstBlock;
                FirstBlock = NULL;
            }

            CurrentSelect = newitem->ID;
            newitem->isselect = true;

            BlockBuilder l_builder(m_pCurrentProjectView);

            CurrentBlock = l_builder.create(CurrentSelect, BLOCK_INIT_POS_X,BLOCK_INIT_POS_Y,1.0);

            update();

            if(CurrentBlock != NULL)
            {
                CurrentBlock->setScale(1);
                QPointF temppos = event->screenPos();
                QPoint temppos1 = m_pCurrentProjectView->mapFromGlobal(temppos.toPoint());
                temppos1.setY(temppos1.y() - CurrentBlock->boundingRect().height()*0.2);
                if(temppos1.y()<5)
                    temppos1.setY(5);

                QPointF temppos2 = m_pCurrentProjectView->mapToScene(temppos1);

                qDebug()<<"CurrentBlock != NULL"<<"temppos"<<temppos<<"temppos1"<<temppos1<<"temppos2"<<temppos2;
                FirstBlock = CurrentBlock;
                if(FirstBlock != NULL){
                    isPress = true;
                    qDebug()<<"get it"<<FirstBlock->getMyText();
                }
            }else{
                qDebug()<<"CurrentBlock = NULL";
            }
        }
    }
    return;
}

void BlockPalette::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    if (FirstBlock == NULL)
    {
        return;
    }

    if(FirstBlock!=NULL)
    {
        QPoint posgloable = event->globalPos();
        QPoint viewpos = m_pCurrentProjectView->mapFromGlobal(posgloable);
        QPointF scenepos = m_pCurrentProjectView->mapToScene(viewpos);

        if((viewpos.x()<0)){
            if(FirstBlock != NULL){
                FirstBlock->setVisible(true);
                FirstBlock->setPos(scenepos.x(),scenepos.y()-FirstBlock->boundingRect().height()/2);
            }

            if(FirstBlock!=NULL)
            {
                if (FirstBlock->prenode != NULL)
                {
                    if (FirstBlock->prenode->leftnode == FirstBlock)
                        FirstBlock->prenode->leftnode = NULL;
                    if (FirstBlock->prenode->rightnode == FirstBlock)
                        FirstBlock->prenode->rightnode = NULL;
                    if (FirstBlock->prenode->stepNode == FirstBlock)
                        FirstBlock->prenode->stepNode = NULL;
                    if (FirstBlock->prenode->nextnode == FirstBlock)
                        FirstBlock->prenode->nextnode = NULL;
                    FirstBlock->prenode->updateAllConnectPos();
                    FirstBlock->prenode->updateConnetLine();
                }
                FirstBlock->DelList(FirstBlock);
                FirstBlock = NULL;
                CurrentSelect = -1;
            }
            CurrentBlock = NULL;
            isPress = false;
            return;
        }else{
            if((viewpos.x()>=0)){
                if(FirstBlock != NULL){
                    FirstBlock->setVisible(true);

                    if (scenepos.y()-FirstBlock->boundingRect().height()/2 < 0)
                        FirstBlock->setPos(scenepos.x(), 0);
                    else
                        FirstBlock->setPos(scenepos.x(),scenepos.y()-FirstBlock->boundingRect().height()/2);
                }
            }else{
                if(FirstBlock!=NULL)
                {
                    qDebug()<<"ccc ID = "<<CurrentSelect;
                    if(FirstBlock->nextnode!=NULL){
                        FirstBlock->nextnode = NULL;
                    }

                    //delete FirstBlock;
                    FirstBlock->DelList(FirstBlock);
                    FirstBlock = NULL;
                }
                CurrentBlock = NULL;
                isPress = false;
                return;
            }
        }
        //FirstBlock->setPos(scenepos.x(),scenepos.y()-FirstBlock->boundingRect().height()/2);
    }

    bool bConnect = FirstBlock->dealCollision();

    //没连接
    if (false == bConnect && FirstBlock->prenode != NULL)
    {
        FirstBlock->prenode->cubline->setVisible(false);
        FirstBlock->prenode->cubline->update();

        if (FirstBlock->prenode->nextnode == FirstBlock)
        {
            FirstBlock->prenode->nextnode = NULL;
        }
        else if (FirstBlock->prenode->leftnode == FirstBlock)
        {
            FirstBlock->prenode->leftnode = NULL;
        }
        else if (FirstBlock->prenode->rightnode == FirstBlock)
        {
            FirstBlock->prenode->rightnode = NULL;
        }
        else if (FirstBlock->prenode->stepNode == FirstBlock)
        {
            FirstBlock->prenode->stepNode = NULL;
        }

        //
        FirstBlock->prenode->updateAllConnectPos();
        FirstBlock->prenode->updateConnetLine();
        //FirstBlock->prenode->updateConnetLine();
        FirstBlock->prenode = NULL;
    }

    if (bConnect == true)
    {
        //if while for
        FirstBlock->updateNodePos();
        FirstBlock->updateAllConnectPos();
        FirstBlock->updateConnetLine();
        //FirstBlock->updateConnetLine();
    }
    else
    {
        FirstBlock->updateConnetLine();
        //FirstBlock->updateConnetLine();
    }

    //    if (FirstBlock->dealCollision()  == true)
    //    {
    //        FirstBlock->updateSelfPos();
    //        FirstBlock->prenode->drawLine();
    //        if (FirstBlock->alwaysUpdateCubLine())
    //            FirstBlock->drawLine();
    //        FirstBlock->updateAllConnectPos();
    //        FirstBlock->updateConnetLine();
    //    }
    //    else
    //    {
    //        if (FirstBlock->alwaysUpdateCubLine())
    //            FirstBlock->drawLine();
    //    }

    FirstBlock->scene()->update();

    isPress = false;

    FirstBlock = NULL;
    CurrentBlock = NULL;
    return;

}
void BlockPalette::mouseMoveEvent(QMouseEvent *event)
{
    if(isPress)
    {
        QPoint pos = this->mapToGlobal(event->pos());
        QPointF pp = m_pCurrentProjectView->mapFromGlobal(pos);
        QPointF pp1 = m_pCurrentProjectView->mapToScene(pp.toPoint());
        qDebug()<<"pp = "<<pp<<"pp1 = "<<pp1;
        if(pp.x()>=0)
        {
            if(FirstBlock!=NULL)
            {
                if (FirstBlock->cubline)
                    FirstBlock->cubline->setVisible(true);
                if (FirstBlock->cubline_left)
                    FirstBlock->cubline_left->setVisible(true);
                if (FirstBlock->cubline_right)
                    FirstBlock->cubline_right->setVisible(true);
                m_pCurrentProjectView->scene()->update();

                if (pp1.y()-FirstBlock->boundingRect().height()/2 < 0)
                    FirstBlock->setPos(pp1.x(), 0);
                else
                    FirstBlock->setPos(pp1.x(),pp1.y()-FirstBlock->boundingRect().height()/2);

                if(FirstBlock!=NULL)
                {
                    if(FirstBlock->nextnode!=NULL)
                    {
                        FirstBlock->nextnode->setPos(pp1.x(),pp1.y()+BLOCK_END_DIS);
                    }
                }

                QGraphicsSceneMouseEvent event;
                event.setPos(pp1);
                event.setScenePos(pp1);
                FirstBlock->SetTree(FirstBlock,&event);
            }

            return;
        }else if((pp.x()<0)){
            QGraphicsView::mouseMoveEvent(event);
            if(FirstBlock != NULL){
                FirstBlock->setVisible(true);
                FirstBlock->setPos(pp1.x(),pp1.y()-FirstBlock->boundingRect().height()/2);
            }
            if (FirstBlock->prenode != NULL)
            {
                if (FirstBlock->prenode->leftnode == FirstBlock)
                    FirstBlock->prenode->leftnode = NULL;
                if (FirstBlock->prenode->rightnode == FirstBlock)
                    FirstBlock->prenode->rightnode = NULL;
                if (FirstBlock->prenode->stepNode == FirstBlock)
                    FirstBlock->prenode->stepNode = NULL;
                if (FirstBlock->prenode->nextnode == FirstBlock)
                    FirstBlock->prenode->nextnode = NULL;
                FirstBlock->prenode->updateAllConnectPos();
                FirstBlock->prenode->updateConnetLine();
            }
            if((pp.x()<-10)){
                if (FirstBlock != NULL)
                {
                    if (FirstBlock->cubline)
                        FirstBlock->cubline->setVisible(true);
                    if (FirstBlock->cubline_left)
                        FirstBlock->cubline_left->setVisible(true);
                    if (FirstBlock->cubline_right)
                        FirstBlock->cubline_right->setVisible(true);
                    FirstBlock->updateConnetLine();
                    m_pCurrentProjectView->scene()->update();
                }
            }
        }
        else
        {
            QGraphicsView::mouseMoveEvent(event);
        }
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }

    return;
}

void BlockPalette::wheelEvent(QWheelEvent *event)
{
    QGraphicsView::wheelEvent(event);
}

BaseBlock *BlockPalette::findBlock(QGraphicsItem* target)
{
    if(target == NULL)
    {
        return NULL;
    }

    BaseBlock* block = dynamic_cast<BaseBlock*>(target);

    while (block == NULL && target->parentItem() != NULL) {

        target = target->parentItem();
        block = dynamic_cast<BaseBlock*>(target);
    }

    return block;
}
