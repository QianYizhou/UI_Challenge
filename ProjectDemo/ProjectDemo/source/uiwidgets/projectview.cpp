#include "projectview.h"
#include <QGraphicsView>
#include <QLabel>
#include <QDragEnterEvent>
#include <QElapsedTimer>
#include <QMimeData>
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include "../define.h"
#include "../Blocks/baseblock.h"
#include "math.h"
#include <QScrollBar>
#include "../util/myfont.h"
#include "../Blocks/percubeline.h"
#include "../Blocks//block_if.h"
#include "../Blocks/block_while.h"
#include "../Blocks/block_for.h"

QElapsedTimer elapsed1;
qreal totalScaleFactor = 1.0;
extern bool TWOVIEWPOINTED;
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
BaseBlock *CurrentBlock = NULL;
extern QString SandBoxPath;


ProjectView::ProjectView(QGraphicsScene *scene, QWidget*parent) :
    QGraphicsView(scene,parent)
{
    setAcceptDrops(true);
    setFrameStyle(Sunken | StyledPanel);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
    setRenderHint(QPainter::Antialiasing, true);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    this->setStyleSheet("background:#00fda6;border: none;");

    ViewInit();

}

ProjectView::~ProjectView()
{

}

void ProjectView::ViewInit()
{
    //还原正常大小
    QMatrix matrix;
    totalScaleFactor = 1.0;
    matrix.scale(totalScaleFactor, totalScaleFactor);
    this->setMatrix(matrix);

    m_pMain = new DisplayBlock(":res/images/block/main_main.png",BLOCK_START);

    m_pMain->setFlag(QGraphicsItem::ItemIsMovable,false);
    m_pMain->setFlag(QGraphicsItem::ItemIsSelectable,false);
    //原点换成画布中心
    m_pMain->SetInit("",tr("开始"), this,
                     this->horizontalScrollBar()->maximum()/2,
                     104 + this->verticalScrollBar()->maximum()/2,
                     1.0);
    this->scene()->addItem(m_pMain);

    m_pRoot = m_pMain;

}

void ProjectView::contextMenuEvent(QContextMenuEvent *event)
{
    QGraphicsView::contextMenuEvent(event);
}

void ProjectView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        QGraphicsView::dragEnterEvent(event);
    }
}

void ProjectView::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        QGraphicsView::dragMoveEvent(event);
    }
}

void ProjectView::dropEvent(QDropEvent *event)
{
    QGraphicsView::dropEvent(event);
}

void ProjectView::keyPressEvent(QKeyEvent * event)
{
    if(event->key()==16777249 )
        isctrl = true;
    if(event->key()==16777251)
        isalt = true;
    QGraphicsView::keyPressEvent(event);
}

void ProjectView::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key()==16777249 )
        isctrl = false;
    if(event->key()==16777251)
        isalt = false;
    QGraphicsView::keyReleaseEvent(event);
}

void ProjectView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
    return;
}

void ProjectView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    elapsed1.start();
    QGraphicsItem *item = this->itemAt(event->pos());
    if (item != NULL)
    {
        CurrentBlock = dynamic_cast<BaseBlock*>(this->itemAt(event->pos()));
        if (NULL == CurrentBlock)
            CurrentBlock = dynamic_cast<BaseBlock*>(item->parentItem());
    }
    else
    {
        CurrentBlock = NULL;

        if(event->button()==Qt::LeftButton&&dragMode()==RubberBandDrag
           && contentsRect().contains(event->pos()))
        {
           m_PressPos = event->pos();
           isPress = true;
        }

    }
}


void ProjectView::mouseMoveEvent(QMouseEvent *event)
{
    if(isPress){
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ProjectView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    qDebug()<<"ProjectView::mouseReleaseEvent = "<<event->globalPos()<<this->geometry();
    //del item
    if(CurrentBlock!=NULL) //CurrentBlock!=NULL 表示点中了一个Block
    {
        if(event->globalPos().x()<=595)
        {
            if(CurrentBlock != NULL && CurrentBlock->ID != BLOCK_START)
            {
                if (CurrentBlock->prenode != NULL)
                {
                    if (CurrentBlock->prenode->leftnode == CurrentBlock)
                        CurrentBlock->prenode->leftnode = NULL;
                    if (CurrentBlock->prenode->rightnode == CurrentBlock)
                        CurrentBlock->prenode->rightnode = NULL;
                    if (CurrentBlock->prenode->stepNode == CurrentBlock)
                        CurrentBlock->prenode->stepNode = NULL;
                    if (CurrentBlock->prenode->nextnode == CurrentBlock)
                        CurrentBlock->prenode->nextnode = NULL;
                    CurrentBlock->prenode->updateAllConnectPos();
                    CurrentBlock->prenode->updateConnetLine();
                }
                CurrentBlock->DelList(CurrentBlock);
            }
            CurrentBlock = NULL;
#if defined Q_OS_LINUX_MY
            if(CurrentBlock != NULL && CurrentBlock->ID != BLOCK_START)
            {
                if(CurrentBlock->pos().x() < -250 * g_fScaleX){
                    CurrentBlock->setPos(0, CurrentBlock->y());
                    if(CurrentBlock->next != NULL){
                        CurrentBlock->updateAllConnectPos();
                        CurrentBlock->updateConnetLine();
                    }
                }
            }
#endif
        }else{
            CurrentBlock->setSelected(false);
            if(CurrentBlock->ID != BLOCK_START)
            {
                if(CurrentBlock->pos().x() < -250 * g_fScaleX){
                    CurrentBlock->setPos(0, CurrentBlock->y());
                    if(CurrentBlock->next != NULL){
                        CurrentBlock->updateAllConnectPos();
                        CurrentBlock->updateConnetLine();
                    }
                }
            }
        }

    }
    else
    {
        if(event->button()==Qt::LeftButton
                && dragMode()==RubberBandDrag
           && contentsRect().contains(event->pos())
               && isPress)
        {
            QPoint releasePos = event->pos();
        }
    }

    resetSystemSelectedStatus();

    isPress = false;

    CurrentBlock = NULL;
}

void ProjectView::resetSystemSelectedStatus()
{
    QList<QGraphicsItem*> l_items = scene()->selectedItems();

    for(QList<QGraphicsItem*>::iterator l_begin = l_items.begin(); l_begin != l_items.end(); l_begin++)
    {
        (*l_begin)->setSelected(false);
    }
}

void ProjectView::resizeEvent(QResizeEvent * event )
{
    QGraphicsView::resizeEvent(event);
}
