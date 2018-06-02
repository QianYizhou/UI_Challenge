#include "baseblock.h"
#include <QPixmap>
#include <QDebug>
#include <QApplication>
#include <QScreen>
#include <QGraphicsView>
#include "../define.h"
#include <QElapsedTimer>

QElapsedTimer elapsedTimer;

extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int BLOCK_PER_DISTANCE;
extern BaseBlock *currentpro;
extern BaseBlock *copyblock;
extern BaseBlock *coopySelectItem;
extern BaseBlock *CurrentBlock;

bool codeModified = false;
extern int CurrentSelect;
QString GetCodeFunc(BaseBlock* p_Block)
{
    return p_Block->GetCode();
}

QString GetCCodeFunc(BaseBlock* p_Block)
{
    return p_Block->GetCCode();
}

BaseBlock::BaseBlock()
{

}

BaseBlock::BaseBlock(QPixmap p,int id):QGraphicsItem()
  , cubline(NULL)
  , cubline_left(NULL)
  , cubline_right(NULL)
  , leftnode(NULL)
  , rightnode(NULL)
  , nextnode(NULL)
  , prenode(NULL)
  , stepNode(NULL)
  , nextStep(NULL)
  , left(NULL)
  , right(NULL)
  , next(NULL)
  , collisionBlock(NULL)
  , myline(NULL)
  , anim(NULL)
{
    setCacheMode(DeviceCoordinateCache);

    circleinside = 0;

    this->left = NULL;
    this->right = NULL;
    this->next = NULL;
    cubline = NULL;

    ID = id;

    leaf = 0;

    LeftTotalcnt = 0;
    RightTotalcnt = 0;
    Leftcnt = 0;
    Rightcnt = 0;


    anim = new QPropertyAnimation();
    anim->setTargetObject(this);
    anim->setPropertyName("pos");
    anim->setDuration(500);

    anim->setEasingCurve(QEasingCurve::OutBounce);

    setFlag(QGraphicsItem::ItemIsFocusable);

    isMove = false;

    cnt = 0;

    LineLeft = 0;
    LineRight = 0;


    Layerno = 0;

    setAcceptedMouseButtons(Qt::LeftButton);
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    if(id == BLOCK_IF)
    {
        left = new ConnectBlock(LEFT);
        right = new ConnectBlock(RIGHT);

        left->setToolTip("LEFT");
        right->setToolTip("RIGHT");

        left->setParentItem(this);
        right->setParentItem(this);

        left->setPos(-left->boundingRect().width()-1,0);
        right->setPos(this->boundingRect().width()+10,0);


    }

    next = new ConnectBlock(NEXT);
    next->setParentItem(this);
    next->setPos(0,this->boundingRect().height()+1);
    next->setToolTip("NEXT");
    if(id == BLOCK_WHILE  || id == BLOCK_FOR )
    {
        left = new ConnectBlock(NEXT);
        left->setParentItem(this);
        left->setPos(0,this->boundingRect().height()+1);

        left->setToolTip("LEFT");
        next->setToolTip("NEXTISHAVE");
    }

    myline = new QGraphicsLineItem(0,0,0,0);
    this->leftnode=NULL;
    this->rightnode=NULL;
    this->nextnode=NULL;
    this->prenode=NULL;
    this->stepNode = NULL;


    isfirst = true;


    you = false;

    QColor ccc = QColor(22,159,211);
    QPen penline(ccc, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    QPainterPath path(QPointF(0,0));
    cubline = new PerCubeLine(path);
    cubline->setPen(penline);


    cubline->setVisible(false);

    isConnect = false;
}

BaseBlock::BaseBlock(QString file, int id, int type):
    cubline(NULL)
  , cubline_left(NULL)
  , cubline_right(NULL)
  , leftnode(NULL)
  , rightnode(NULL)
  , nextnode(NULL)
  , prenode(NULL)
  , stepNode(NULL)
  , nextStep(NULL)
  , left(NULL)
  , right(NULL)
  , next(NULL)
  , collisionBlock(NULL)
  , myline(NULL)
  , anim(NULL)
  , pixmapPath(file)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    setMyPixmap(file, QSize(434 * ss, 164 * ss));
    update();

    setBlockType(type);
    ID = id;
    dispoint = QPointF(-1000,-1000);

    QColor ccc = QColor(22,159,211);
    QPen penline(ccc, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPainterPath path(QPointF(0,0));
    cubline = new PerCubeLine(path);
    cubline->setPen(penline);
    cubline->setVisible(false);

    next = NULL;
    left = NULL;
    right = NULL;
    cubline_left = NULL;
    cubline_right = NULL;

    m_bShow = false;

}

BaseBlock::BaseBlock(const QString &file, const QString &text, QSize imagesize)
{
    setMyText(text);
    setMyPixmap(file,imagesize);
}

BaseBlock::~BaseBlock()
{
    qDebug()<<"BaseBlock::~BaseBlock()";
}

void BaseBlock::setBaseBlockID(int id)
{
    ID = id;
}

int BaseBlock::getBaseBlockID() const
{
    return ID;
}

void BaseBlock::setBlockType(const int &type)
{
    blockType = type;
}

int BaseBlock::getBlockType()
{
    return blockType;
}

void BaseBlock::setIconPixmap(const QPixmap &pixmap)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    iconPixmap = pixmap;

    QSize size;
    iconPixmap = pixmap.copy(0.0, 0.0, 184, 191 - 0);

    {
        QSize size2(120,120);
        size = size2;
    }

    iconPixmap = iconPixmap.scaled(size.width()*QApplication::primaryScreen()->devicePixelRatio()*ss,
                       size.height()*QApplication::primaryScreen()->devicePixelRatio()*ss);
    iconPixmap.setDevicePixelRatio(QApplication::primaryScreen()->devicePixelRatio());
    m_picon = new QGraphicsPixmapItem(iconPixmap, this);
    m_picon->setCacheMode(DeviceCoordinateCache);

    //添加左上角的图标
    // 命令模块中 中断、退出、继续循环三个模块有小图标
    if(blockType == MODULELIB_CONTROLER || ID == BLOCK_BREAK || ID == BLOCK_CONTINUE ||
            ID == BLOCK_RETURN){
        m_picon->setPos(3.0 * g_fScaleX, -10.0 * g_fScaleY);
    }else if(blockType == MODULELIB_SENSOR){
        m_picon->setPos(20.0 * g_fScaleX, -10.0 * g_fScaleY);
    }else{
        m_picon->setPos(0,0);
    }

    update();
}

void BaseBlock::setIconPixmap(const QString &pixmapstr)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    QPixmap pixmap(pixmapstr);
    if (pixmap.isNull() || BLOCK_IF == ID || BLOCK_FOR == ID || BLOCK_WHILE == ID)
        return;

    QSize size;
    iconPixmap = pixmap.copy(0.0, 0.0, 184, 191 - 0);
    {
       size = QSize(120,120 /*45,45*/);
       iconPixmap = iconPixmap.scaled(size);
    }

    m_picon = new QGraphicsPixmapItem(QPixmap(iconPixmap).scaled(size.width() * g_fScale,size.height() * g_fScale), this);
    m_picon->setCacheMode(DeviceCoordinateCache);

    //添加左上角的图标
    // 命令模块中 中断、退出、继续循环三个模块有小图标
    if(blockType == MODULELIB_CONTROLER || ID == BLOCK_BREAK || ID == BLOCK_CONTINUE ||
             ID == BLOCK_RETURN){
        m_picon->setPos(3.0 * g_fScaleX, -10.0 * g_fScaleY);
    }else if(blockType == MODULELIB_SENSOR){
        m_picon->setPos(20.0 * g_fScaleX, -10.0 * g_fScaleY);
    }else{
        m_picon->setPos(0,0);
    }

    update();
}

QPixmap BaseBlock::getIconPixmap()
{
    return iconPixmap;
}

void BaseBlock::setMyText(const QString &text)
{
    filepath = text;
    myText = text;
}

void BaseBlock::setMyPixmap(const QString &file,QSize size)
{
    m_pbackground = new QGraphicsPixmapItem(QPixmap(file).
                                            scaled(size.width(),
                                                   size.height()), this);
    m_pbackground->setZValue(-1);
}

void BaseBlock::setMyPixmap(const QPixmap& pixmap)
{
    m_pbackground = new QGraphicsPixmapItem(QPixmap(pixmap), this);
    m_pbackground->setZValue(-1);
}

QRectF BaseBlock::boundingRect() const
{
    QRect rect = m_pbackground->pixmap().rect();
    return QRectF(0,0,rect.width(),
                  rect.height());
}

void BaseBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    return;
}

QPainterPath BaseBlock::shape() const
{
    QRectF rect = this->m_pbackground->pixmap().rect();

    QPainterPath path;
    path.addRoundRect(rect, 5,5);
    return path;
}

void BaseBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    elapsedTimer.start();

    m_bMoved = false;
    QGraphicsItem::mousePressEvent(event);
}

void BaseBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"BaseBlock::mouseReleaseEvent"<<this->ID<<event->pos();
    QGraphicsItem::mouseReleaseEvent(event);

    if (false == m_bMoved /*|| (elapsedTimer.isValid() && elapsedTimer.elapsed() < 200
                              && abs(m_pProjectView->mapFromScene(event->pos()).x() - startPoint.x()) < 20
                              && abs(m_pProjectView->mapFromScene(event->pos()).y() - startPoint.y()) < 20)*/ )
    {
        /*qreal x = this->x() + this->boundingRect().width() + 290*g_fScaleX;
        qreal y = this->y() + 100*g_fScaleY;
        x = this->x() + this->boundingRect().width() + 570*g_fScaleX;
        y = this->y() + 370*g_fScaleY;
        QPoint mypos = m_pProjectView->mapFromScene(x,y);
        QSize widgetSize = getWidgetSize();
        qDebug()<<"mypos = "<<mypos;
        qDebug()<<"QApplication::primaryScreen()->size() = "<<QApplication::primaryScreen()->size();
        if ((mypos.x() + widgetSize.width()) > QApplication::primaryScreen()->size().width()){
            x = this->x() - ((widgetSize.width() - 545 * g_fScaleX) + 220*g_fScaleX);
            mypos = m_pProjectView->mapFromScene(x,y);
            if(mypos.x() < 0){mypos.setX(0);}
        }

        if ((mypos.y() + widgetSize.height()) > QApplication::primaryScreen()->size().height()){
            mypos.setY(mypos.y() - widgetSize.height() + 165 * g_fScaleY);
        }
        qDebug()<<" back mypos = "<<mypos<<"widgetSize ="<<widgetSize;
        if (elapsedTimer.elapsed() < 300)
        {
            if(event->button() == Qt::LeftButton)
            {
#if defined Q_OS_LINUX_MY
            ShowDialog(mypos);
#else
            if (true == g_bIpad)
                ShowDialog(mypos);
            else
                ShowDialog(QPoint((QApplication::primaryScreen()->size().width() - widgetSize.width())/2,
                                  (QApplication::primaryScreen()->size().height() - widgetSize.height())/2));
#endif
            }
            else
            {
                m_pProjectView->onCopyTimeout();
            }

            codeModified = true;

        }*/

        elapsedTimer.invalidate();

        this->updateNodePos();
        updateAllConnectPos();
        updateConnetLine();
        return;
    }

    if(elapsedTimer.isValid()){
        elapsedTimer.invalidate();
    }

    bool bConnect = dealCollision();

    //没连接
    if (false == bConnect && this->prenode != NULL)
    {
        this->prenode->cubline->setVisible(false);
        this->prenode->cubline->update();

        if (this->prenode->nextnode == this)
        {
            this->prenode->nextnode = NULL;
        }
        else if (this->prenode->leftnode == this)
        {
            this->prenode->leftnode = NULL;
        }
        else if (this->prenode->rightnode == this)
        {
            this->prenode->rightnode = NULL;
        }
        else if (this->prenode->stepNode == this)
        {
            this->prenode->stepNode = NULL;
        }

        //
        this->prenode->updateAllConnectPos();
        //this->prenode->updateConnetLine();
        this->prenode->updateConnetLine();
        this->prenode = NULL;
    }

    if (bConnect == true)
    {
        this->updateNodePos();
        //if while for
        updateAllConnectPos();
        //updateConnetLine();
        updateConnetLine();
    }
    else
    {
        //this->updateConnetLine();
        this->updateConnetLine();
    }

    this->scene()->update();
    update(this->m_pbackground->pixmap().rect());
}

void BaseBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << " BaseBlock::mouseMoveEvent ";

    m_bMoved = true;
    QPointF prevPos = this->pos();
    SetTree(this,event);
    QGraphicsItem::mouseMoveEvent(event);
    if (this->pos().y() < 0)
        this->setY(0);
    QPointF movingPos = this->pos();

    bool bConnect = dealCollision();

    //没连接
    if (false == bConnect && this->prenode != NULL)
    {
        this->prenode->cubline->setVisible(false);
        this->prenode->cubline->update();

        if (this->prenode->nextnode == this)
        {
            this->prenode->nextnode = NULL;
        }
        else if (this->prenode->leftnode == this)
        {
            this->prenode->leftnode = NULL;
        }
        else if (this->prenode->rightnode == this)
        {
            this->prenode->rightnode = NULL;
        }
        else if (this->prenode->stepNode == this)
        {
            this->prenode->stepNode = NULL;
        }

        //
        this->prenode->updateAllConnectPos();
        //this->prenode->updateConnetLine();
        this->prenode->updateConnetLine();
        this->prenode = NULL;
    }


    this->updateConnectNode(movingPos.x() - prevPos.x(),
                            movingPos.y() - prevPos.y());
    //this->updateConnetLine();
    this->updateConnetLine();
    this->scene()->update();

}

void BaseBlock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    //双击
}

QString BaseBlock::getMyText()
{
    return myText;
}

void BaseBlock::SetInit(QString iconstr, QString tip, QGraphicsView *p_pProjectView, int x, int y, qreal real)
{
    qreal ss = g_fScaleX <= g_fScaleY ? g_fScaleX : g_fScaleY;
    setIconPixmap(iconstr);


    this->setPos(x,y);
    qDebug()<<"BaseBlock::SetInit ID = "<<ID<<"X="<<x<<"Y="<<y;
    this->dispoint = QPoint(x,y);

    this->setVisible(true);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setMyText(tip);
    if(p_pProjectView)
        p_pProjectView->scene()->addItem(this);
    this->setScale(1);

    next = new ConnectBlock(NEXT);
    next->setParentItem(this);
    next->setToolTip("NEXT");
    next->setPos(this->boundingRect().width()/2-next->boundingRect().width()/2,
                 this->boundingRect().height()-26*g_fScaleY);

    collisionBlock = new ConnectBlock(COLLSION);
    collisionBlock->setParentItem(this);
    collisionBlock->setToolTip("COLLSION");
    collisionBlock->setPos(this->boundingRect().width()/2-next->boundingRect().width()/2,
                           0);

    if(p_pProjectView)
        p_pProjectView->scene()->addItem(this->cubline);
    this->cubline->setZValue(-10);
}

void BaseBlock::SetTree(BaseBlock *node,QGraphicsSceneMouseEvent *event)
{
    node->cnt = 0;

    node->isMove = true;

    node->you = false;

    bool bConnect = dealCollision();

    //没连接
    if (false == bConnect && this->prenode != NULL)
    {
        this->prenode->cubline->setVisible(false);
        this->prenode->cubline->update();

        if (this->prenode->nextnode == this)
        {
            this->prenode->nextnode = NULL;
        }
        else if (this->prenode->leftnode == this)
        {
            this->prenode->leftnode = NULL;
        }
        else if (this->prenode->rightnode == this)
        {
            this->prenode->rightnode = NULL;
        }
        else if (this->prenode->stepNode == this)
        {
            this->prenode->stepNode = NULL;
        }

        //
        this->prenode->updateAllConnectPos();
        this->prenode->updateConnetLine();
        this->prenode->updateConnetLine();
        this->prenode = NULL;
    }

    if (this->prenode != NULL)
    {
        this->prenode->drawLine();
        this->prenode->drawLine();
    }

    this->updateConnetLine();
    this->scene()->update();
}

void BaseBlock::DelList(BaseBlock *node)
{
    if (node==NULL)
        return;

    if(node->leftnode!=NULL)
        node->leftnode->DelList(node->leftnode);
    if(node->rightnode!=NULL)
        node->rightnode->DelList(node->rightnode);
    if(node->stepNode!=NULL)
        node->stepNode->DelList(node->stepNode);
    if(node->nextnode!=NULL)
    {
        node->nextnode->DelList(node->nextnode);
    }

    if(node->prenode!=NULL)
    {
        if(node->prenode->leftnode!=NULL)
        {
            if(node->prenode->leftnode==node)
                node->prenode->leftnode = NULL;
        }
        if(node->prenode->rightnode!=NULL)
        {
            if(node->prenode->rightnode==node)
                node->prenode->rightnode = NULL;
        }
        if(node->prenode->nextnode!=NULL)
        {
            if(node->prenode->nextnode==node)
                node->prenode->nextnode = NULL;
        }
        if(node->prenode->stepNode!=NULL)
        {
            if(node->prenode->stepNode==node)
                node->prenode->stepNode = NULL;
        }
    }

    if (node->cubline)
    {
        node->scene()->removeItem(node->cubline);
        delete node->cubline;
        node->cubline = NULL;
    }

    if (node->cubline_left)
    {
        node->scene()->removeItem(node->cubline_left);
        delete node->cubline_left;
        node->cubline_left = NULL;
    }

    if (node->cubline_right)
    {
        node->scene()->removeItem(node->cubline_right);
        delete node->cubline_right;
        node->cubline_right = NULL;
    }

//    m_pProjectView->scene()->removeItem(node);
//    m_pProjectView->scene()->update();
    delete node;
    node = NULL;
}

void BaseBlock::ask(BaseBlock *node)
{
    if(node->leftnode!=NULL)
    {
        ask(node->leftnode);
    }
    if(node->rightnode!=NULL)
    {
        ask(node->rightnode);
    }
    if(node->nextnode!=NULL)
    {
        ask(node->nextnode);
    }
    if(node!=NULL)
    {
        node->setScale(1.2);
    }
}

void BaseBlock::updateNodePos()
{
    //    qDebug("BaseBlock::updateNodePos()");
    if (this->prenode == NULL)
        return;

    //if (this->ID == BLOCK_FOR)
    // qDebug("ID = %d  x() = %f", this->ID,this->x());

    do {

        //        if (this->prenode->ID == 0)
        //            break;

        if (this->prenode->leftnode == this)
        {
            //qDebug("(this->prenode->leftnode == this)");
            this->setPos(this->prenode->x() - this->boundingRect().width()/2 - 26,
                         this->prenode->y() + this->prenode->boundingRect().height() + BLOCK_PER_DISTANCE);
            //qDebug("leftNode  %f", this->x());
        }
        else if (this->prenode->rightnode == this)
            this->setPos(this->prenode->x() + this->boundingRect().width()/2 + 26,
                         this->prenode->y() + this->prenode->boundingRect().height() + BLOCK_PER_DISTANCE);
        else if (this->prenode->stepNode == this)
        {
            //qDebug("ID = %d stepNode  %f", this->prenode->ID,this->prenode->x());
            //qDebug("stepNode  %f", this->x());
            this->setPos(this->prenode->x(),
                         this->prenode->y() + this->prenode->boundingRect().height() + BLOCK_PER_DISTANCE);
            //qDebug("stepNode  %f", this->x());
        }
        else if (this->prenode->nextnode == this)
        {
            //qDebug("this  ID = %d this.x  %f", this->ID,this->x());
            //qDebug("this->prenode->ID = %d     this->prenode.x  %f", this->prenode->ID,this->prenode->x());
            this->setPos(this->prenode->x(),
                         this->prenode->y() + this->prenode->next->y() + BLOCK_PER_DISTANCE);
        }

    }while(0);

    //qDebug("update end this.x  %f", this->x());

    if (this->leftnode != NULL)
        this->leftnode->updateNodePos();
    if (this->rightnode != NULL)
        this->rightnode->updateNodePos();
    if (this->stepNode != NULL)
        this->stepNode->updateNodePos();
    if (this->nextnode != NULL)
        this->nextnode->updateNodePos();


    //    updateNodePos(node->leftnode);
    //    updateNodePos(node->rightnode);
    //    updateNodePos(node->nextnode);
}

void BaseBlock::updateChildPos()
{
    if (this->nextnode == NULL)
        return;

    //qDebug("BaseBlock::updateChildPos()");
    this->nextnode->setPos(this->x(),
                           this->y() + this->next->y() + BLOCK_PER_DISTANCE);
    this->nextnode->updateChildPos();
    //    if (this->nextnode->nextnode == this)
    //        this->setPos(this->prenode->x(),
    //                     this->prenode->y() + this->prenode->next->y() + BLOCK_PER_DISTANCE);
    //    else if (this->nextnode->leftnode == this)
    //        this->setPos(this->prenode->x() - this->boundingRect().width()/2 - 26,
    //                     this->prenode->y() + this->prenode->boundingRect().height() + BLOCK_PER_DISTANCE);
    //    else if (this->nextnode->rightnode == this)
    //        this->setPos(this->prenode->x() + this->boundingRect().width()/2 + 26,
    //                     this->prenode->y() + this->prenode->boundingRect().height() + BLOCK_PER_DISTANCE);
}

//void BaseBlock::drawline(BaseBlock *node)
//{
//    if(node->leftnode!=NULL)
//    {
//        QPointF start = node->left->scenePos();
//        start.setX(start.x()+node->left->boundingRect().width());
//        start.setY(start.y()+node->left->boundingRect().height()/2);

//        QPointF endp = node->leftnode->pos();
//        endp.setX(endp.x()+node->leftnode->boundingRect().width()/2);
//        endp.setY(endp.y()+node->leftnode->boundingRect().height()/2);

//        path.moveTo(start);
//        path.cubicTo(node->leftnode->pos().x()+node->leftnode->boundingRect().width()/2,node->left->scenePos().y()+node->left->boundingRect().height()/2,endp.x(),endp.y(),endp.x(),endp.y());

//        node->leftnode->cubline->setPath(path);
//        node->leftnode->cubline->setVisible(true);

//        drawline(node->leftnode);

//    }
//    if(node->rightnode!=NULL)
//    {
//        QPointF start = node->right->scenePos();

//        start.setX(start.x());
//        start.setY(start.y()+node->right->boundingRect().height()/2);

//        QPointF endp = node->rightnode->pos();
//        endp.setX(endp.x()+node->rightnode->boundingRect().width()/2);
//        endp.setY(endp.y()+node->rightnode->boundingRect().height()/2);

//        path.moveTo(start);
//        path.cubicTo(node->rightnode->pos().x()+node->rightnode->boundingRect().width()/2,node->right->scenePos().y()+node->right->boundingRect().height()/2,endp.x(),endp.y(),endp.x(),endp.y());

//        node->rightnode->cubline->setPath(path);
//        node->rightnode->cubline->setVisible(true);

//        drawline(node->rightnode);
//    }
//    if(node->nextnode!=NULL)
//    {
//        QPointF start = node->next->scenePos();

//        start.setX(start.x()+node->next->boundingRect().width()/2);
//        start.setY(start.y());

//        QPointF endp = node->nextnode->pos();
//        endp.setX(endp.x()+node->nextnode->boundingRect().width()/2);
//        endp.setY(endp.y()+node->nextnode->boundingRect().height()/2);

//        path.moveTo(start);
//        path.cubicTo(node->nextnode->pos().x()+node->nextnode->boundingRect().width()/2,node->next->scenePos().y()+node->next->boundingRect().height()/2,endp.x(),endp.y(),endp.x(),endp.y());

//        node->nextnode->cubline->setPath(path);
//        node->nextnode->cubline->setVisible(true);

//        drawline(node->nextnode);
//    }
//}

void BaseBlock::invaline(BaseBlock *node)
{
    if(node->leftnode!=NULL)
    {
        node->leftnode->cubline->setVisible(false);
        invaline(node->leftnode);
    }
    if(node->rightnode!=NULL)
    {
        node->rightnode->cubline->setVisible(false);
        invaline(node->rightnode);
    }
    if(node->nextnode!=NULL)
    {
        node->nextnode->cubline->setVisible(false);
        invaline(node->nextnode);
    }
}

void BaseBlock::drawLine()
{
    if (this->nextnode == NULL)
    {
        this->cubline->setVisible(false);
        return;
    }

    this->nextnode->drawLine();

    QPointF start = this->next->scenePos();

    start.setX(start.x()+this->next->boundingRect().width()/2);

    QPointF endp = this->nextnode->pos();
    endp.setX(endp.x()+this->nextnode->boundingRect().width()/2);

    QPainterPath path(start);
    path.lineTo(endp.x(),endp.y());
    this->cubline->setPath(path);

    this->cubline->setVisible(true);
    this->cubline->update();
}

void BaseBlock::updateConnectNode(qreal Xoffset, qreal Yoffset)
{
    if (this->nextnode != NULL)
    {
        this->nextnode->setPos(this->nextnode->pos().x() + Xoffset,
                               this->nextnode->pos().y() + Yoffset);
        this->nextnode->updateConnectNode(Xoffset, Yoffset);

    }

    if (this->leftnode != NULL)
    {
        this->leftnode->setPos(this->leftnode->pos().x() + Xoffset,
                               this->leftnode->pos().y() + Yoffset);
        this->leftnode->updateConnectNode(Xoffset, Yoffset);
    }

    if (this->rightnode != NULL)
    {
        this->rightnode->setPos(this->rightnode->pos().x() + Xoffset,
                                this->rightnode->pos().y() + Yoffset);
        this->rightnode->updateConnectNode(Xoffset, Yoffset);
    }

    if (this->stepNode != NULL)
    {
        this->stepNode->setPos(this->stepNode->pos().x() + Xoffset,
                               this->stepNode->pos().y() + Yoffset);
        this->stepNode->updateConnectNode(Xoffset, Yoffset);
    }

}

void BaseBlock::updateConnetLine()
{
    //if for while
    BaseBlock* node = this->prenode;

    //this->drawLine();

    while (node != NULL)
    {
        node->drawLine();

        //若前驱节点是被复制状态，更改状态
        if(node->isEffectLight())
        {
            node->showEffectLight(false);
//            m_pProjectView->clearPasteboard();
        }

        node = node->prenode;
    }

    if (this->prenode == NULL)
        this->drawLine();
    //node->drawLine();

    //更新连接节点的位置
    //    if (this->nextnode != NULL)
    //    {
    //        node->drawLine();
    //    }
}

bool BaseBlock::dealCollision()
{
    QList<QGraphicsItem*> items = this->scene()->collidingItems(this->collisionBlock);
    bool bConnect = false;

    //TODO
    for (auto item : items)
    {
        //BLOCK_IF
        if ((item->toolTip() == "LEFT") && item != this->left)
        {
            BaseBlock* p = (BaseBlock*) item->parentItem();
            //碰撞的模块已连接
            if ((p->leftnode != NULL) && (p->leftnode != this))
                continue;

            if (this->prenode != NULL)
            {
                if (this->prenode->nextnode == this)
                {
                    this->prenode->nextnode = NULL;
                }
                if (this->prenode->rightnode == this)
                {
                    this->prenode->rightnode = NULL;
                }
                if (this->prenode->stepNode == this)
                {
                    this->prenode->stepNode = NULL;
                }
                this->prenode->drawLine();
            }
            if (p != this->leftnode)
            {
                if (this->prenode != NULL)
                {
                    this->prenode->leftnode = NULL;
                    this->prenode->drawLine();
                }
                p->leftnode = this;
                this->prenode = p;
            }

            //p->drawLine();
            bConnect = true;
            break;
        }
        //BLOCK_IF
        else if ((item->toolTip() == "RIGHT") && item != this->right)
        {
            BaseBlock* p = (BaseBlock*) item->parentItem();

            //碰撞的模块已连接
            if ((p->rightnode != NULL) && (p->rightnode != this))
                continue;

            if (this->prenode != NULL)
            {
                if (this->prenode->nextnode == this)
                {
                    this->prenode->nextnode = NULL;
                }
                if (this->prenode->leftnode == this)
                {
                    this->prenode->leftnode = NULL;
                }
                if (this->prenode->stepNode == this)
                {
                    this->prenode->stepNode = NULL;
                }
                this->prenode->drawLine();
            }

            if (p != this->rightnode)
            {
                if (this->prenode != NULL)
                {
                    this->prenode->rightnode = NULL;
                    this->prenode->drawLine();
                }
                p->rightnode = this;
                this->prenode = p;
            }

            //p->drawLine();
            bConnect = true;
            break;
        }
        else if ((item->toolTip() == "NEXTSTEP") && item != this->nextStep)
        {
            BaseBlock* p = (BaseBlock*) item->parentItem();

            //碰撞的模块已连接
            if ((p->stepNode != NULL) && (p->stepNode != this))
                continue;

            if (this->prenode != NULL)
            {
                if (this->prenode->nextnode == this)
                {
                    this->prenode->nextnode = NULL;
                }
                if (this->prenode->rightnode == this)
                {
                    this->prenode->rightnode = NULL;
                }
                if (this->prenode->leftnode == this)
                {
                    this->prenode->leftnode = NULL;
                }
                this->prenode->drawLine();
            }

            if (p != this->prenode)
            {
                if (this->prenode != NULL)
                {
                    this->prenode->stepNode = NULL;
                    this->prenode->drawLine();
                }
                p->stepNode = this;
                this->prenode = p;
            }
            else
            {
                if (p->nextnode == this)
                {
                    p->nextnode = NULL;
                }
                p->stepNode = this;
                this->prenode = p;
                p->drawLine();
            }
            bConnect = true;
            break;
        }
        else if ((item->toolTip() == "NEXT") && item != this->next)
        {
            BaseBlock* p = (BaseBlock*) item->parentItem();

            //碰撞的模块已连接
            if ((p->nextnode != NULL) && (p->nextnode != this))
                continue;

            if (this->prenode != NULL)
            {
                if (this->prenode->rightnode == this)
                {
                    this->prenode->rightnode = NULL;
                }
                if (this->prenode->leftnode == this)
                {
                    this->prenode->leftnode = NULL;
                }
                if (this->prenode->stepNode == this)
                {
                    this->prenode->stepNode = NULL;
                }
                this->prenode->drawLine();
            }

            if (p != this->prenode)
            {
                if (this->prenode != NULL)
                {
                    this->prenode->nextnode = NULL;
                    this->prenode->drawLine();
                }
                p->nextnode = this;
                this->prenode = p;
            }
            //p->drawLine();
            bConnect = true;
            break;
        }

    }


    return bConnect;
}

bool BaseBlock::alwaysUpdateCubLine()
{
    return false;
}

int BaseBlock::get_leftCount()
{
    if (this->rightnode == NULL)
        return 0;

    bool contain = false;
    BaseBlock* temp = this->rightnode->leftnode;

    int n = 1;
    int num = 0;
    int num1 = 0;
    temp = this->rightnode;


    while (temp != NULL)
    {
        if (temp->leftnode != NULL || temp->rightnode != NULL)
        {
            contain = true;
            break;
        }

        temp = temp->nextnode;
    }

    if (false == contain)
        return 1;



    BaseBlock* node = temp->leftnode;
    if (node != NULL)
        ++n;

    while (node != NULL)
    {
        num1 = get_leaf(node);
        num = num1 > num ? num1 : num;
        int num2 = get_leaf(node->stepNode);
        num = num2 > num ? num2 : num;

        node = node->nextnode;
    }

    return num+n;
}

int BaseBlock::get_rightCount()
{
    if (this->ID == BLOCK_IF || this->ID == BLOCK_WHILE)
    {

    }

    if (this->leftnode == NULL)
        return 0;

    bool contain = false;
    BaseBlock* temp = NULL;

    int n = 1;
    int num = 0;
    int num1 = 0;
    temp = this->leftnode;

    while (temp != NULL)
    {
        if (temp->leftnode != NULL || temp->rightnode != NULL)
        {
            contain = true;
            break;
        }

        temp = temp->nextnode;
    }

    if (false == contain)
        return 1;


    BaseBlock* node = temp->rightnode;

    if (node != NULL)
        ++n;//2

    while (node != NULL)
    {
        num1 = get_leaf(node);
        num = num1 > num ? num1 : num;
        int num2 = get_leaf(node->stepNode);
        num = num2 > num ? num2 : num;

        node = node->nextnode;
    }

    return num+n;
}

int BaseBlock::get_leaf(BaseBlock *node)
{
    //只对if有效
    while (node != NULL && node->ID != BLOCK_IF)
    {
        node = node->nextnode;
    }

    if (node == NULL)
        return 0;

    int num = 0;
    if (node->leftnode != NULL)
        ++num;
    if (node->rightnode != NULL)
        ++num;

    int self_leaf = num + get_leaf(node->leftnode) + get_leaf(node->rightnode);
    int next_leaf = get_leaf(node->nextnode);
    int loop_leaf = get_leaf(node->stepNode);
    next_leaf = next_leaf > loop_leaf ? next_leaf : loop_leaf;


    return self_leaf > next_leaf ? self_leaf : next_leaf;
    //return num;
}

//只处理循环内部的
int BaseBlock::loop_leaf(BaseBlock *node)
{

    return 0;
}

void BaseBlock::updateAllConnectPos()
{
    //maybe TODO
    BaseBlock* node = this->prenode;
    BaseBlock* specialNode = NULL;

    while (node != NULL)
    {
        if (node->ID == BLOCK_IF)
            specialNode = node;
        node = node->prenode;
    }

    if (NULL == specialNode)
    {
        //if while for
        if (this->ID == BLOCK_IF)
            this->updateChildPos();
        else
        {
            this->updateNodePos();
            this->updateChildPos();
        }
    }
    else
    {
        specialNode->updateChildPos();
    }
}

void BaseBlock::getRectSize(BaseBlock *node, qreal &xLeft, qreal &yButton, qreal &xRight, int &lloop, int &rloop)
{
    if (node == NULL)
        return;
    if (node->ID == BLOCK_WHILE || node->ID == BLOCK_FOR)
    {
        if (node->ID == BLOCK_WHILE)
        {
            /*Block_While* p = (Block_While*)node;
            if (p != NULL)
                getRectSize(p->stepNode, xLeft, yButton, xRight, lloop, rloop);*/
        }

        if (node->ID == BLOCK_FOR)
        {
            /*Block_For* p = (Block_For*)node;
            if (p != NULL)
                getRectSize(p->stepNode, xLeft, yButton, xRight, lloop, rloop);*/
        }

        xLeft = xLeft - 20;
        if (node->x() <= xLeft)
        {
            ++lloop;
            xLeft = node->x() - 20*lloop;
        }

        if (node->y() + node->next->y() > yButton)
            yButton = node->y() + node->next->y();

        xRight = xRight + 20;
        if (node->x() + node->boundingRect().width() >= xRight)
        {
            ++rloop;
            xRight = node->x() + node->boundingRect().width() + 20*rloop;
        }

    }
    else
    {
        if (node->x() < xLeft)
            xLeft = node->x();
        if (node->y() + node->next->y() > yButton)
            yButton = node->y() + node->next->y();
        if (node->x() + node->boundingRect().width() > xRight)
            xRight = node->x() + node->boundingRect().width();
    }

    if (node->leftnode)
        getRectSize(node->leftnode, xLeft, yButton, xRight, lloop, rloop);
    if (node->rightnode)
        getRectSize(node->rightnode, xLeft, yButton, xRight, lloop, rloop);
    if (node->nextnode)
        getRectSize(node->nextnode, xLeft, yButton, xRight, lloop, rloop);
}

void BaseBlock::showEffectLight(bool show, bool effectChild)
{
    m_bShow = show;
    if (effectChild)
    {
        if (this->leftnode != NULL)
            this->leftnode->showEffectLight(show, effectChild);
        if (this->rightnode != NULL)
            this->rightnode->showEffectLight(show, effectChild);
        if (this->stepNode != NULL)
            this->stepNode->showEffectLight(show, effectChild);
        if (this->nextnode != NULL)
            this->nextnode->showEffectLight(show, effectChild);
    }
}

bool BaseBlock::isEffectLight()
{
    return m_bShow;
}

void BaseBlock::showItem(BaseBlock *node, bool show)
{
    if (node == NULL)
        return;

    if (false == show)
    {
//        m_pProjectView->scene()->removeItem(node);
//        if (node->cubline != NULL && node->nextnode!= NULL)
//            m_pProjectView->scene()->removeItem(node->cubline);
//        if (node->cubline_left != NULL)
//            m_pProjectView->scene()->removeItem(node->cubline_left);
//        if (node->cubline_right != NULL)
//            m_pProjectView->scene()->removeItem(node->cubline_right);

        showItem(node->leftnode, show);
        showItem(node->rightnode, show);
        showItem(node->stepNode, show);
        showItem(node->nextnode, show);
    }
    else
    {
//        m_pProjectView->scene()->addItem(node);
//        if (node->cubline != NULL && node->nextnode!= NULL)
//            m_pProjectView->scene()->addItem(node->cubline);
//        if (node->cubline_left != NULL)
//            m_pProjectView->scene()->addItem(node->cubline_left);
//        if (node->cubline_right != NULL)
//            m_pProjectView->scene()->addItem(node->cubline_right);

        showItem(node->leftnode, show);
        showItem(node->rightnode, show);
        showItem(node->stepNode, show);
        showItem(node->nextnode, show);
    }
}

void BaseBlock::deleteItem(BaseBlock *node)
{
    if (node==NULL)
        return;

    if (node->leftnode!=NULL)
        deleteItem(node->leftnode);
    if (node->rightnode!=NULL)
        deleteItem(node->rightnode);
    if (node->stepNode!=NULL)
        deleteItem(node->stepNode);
    if (node->nextnode!=NULL)
        deleteItem(node->nextnode);

    if(node->prenode!=NULL)
    {
        if(node->prenode->leftnode!=NULL)
        {
            if(node->prenode->leftnode==node)
                node->prenode->leftnode = NULL;
        }
        if(node->prenode->rightnode!=NULL)
        {
            if(node->prenode->rightnode==node)
                node->prenode->rightnode = NULL;
        }
        if(node->prenode->nextnode!=NULL)
        {
            if(node->prenode->nextnode==node)
                node->prenode->nextnode = NULL;
        }
        if(node->prenode->stepNode!=NULL)
        {
            if(node->prenode->stepNode==node)
                node->prenode->stepNode = NULL;
        }
    }

    if (node->cubline)
    {
        delete node->cubline;
        node->cubline = NULL;
    }

    if (node->cubline_left)
    {
        delete node->cubline_left;
        node->cubline_left = NULL;
    }

    if (node->cubline_right)
    {
        delete node->cubline_right;
        node->cubline_right = NULL;
    }

    delete node;
    node = NULL;
}

//hds: this pointer is used to identify if this block belongs to
//some 'if' or 'while' block. **Abandoned**.
BaseBlock* BaseBlock::getRecursive()
{
    if(circleinside==0)
        return NULL;

    if(prenode!=NULL&&(prenode->circleinside==circleinside))
        return prenode->getRecursive();

    if(prenode!=NULL&&prenode->circleinside == circleinside-1)
        return prenode;

    return NULL;
}

void BaseBlock::get_rect_head_end(BaseBlock *node_head, BaseBlock *node_end, double &lefttopx, double &lefttopy, double &rightbottomx, double &rightbottomy)
{
    if(node_head==NULL)
    {
        lefttopx = 0;
        lefttopy = 0;
        rightbottomx = 0;
        rightbottomy = 0;
        return;
    }

    {
        if(node_head->GetPos().x()<=lefttopx)
            lefttopx = node_head->GetPos().x();
    }

    {
        if(node_head->pos().x()+node_head->boundingRect().width()>=rightbottomx)
            rightbottomx = node_head->pos().x() + node_head->boundingRect().width();
    }

    if(node_head->pos().y()+node_head->boundingRect().height()>=rightbottomy)
        rightbottomy = node_head->pos().y() + node_head->boundingRect().height();

    if(node_head==node_end)
    {
        return;
    }
    if(node_head->leftnode!=NULL)
    {
        get_rect_head_end(node_head->leftnode,node_end,lefttopx,lefttopy,rightbottomx,rightbottomy);
    }

    if(node_head->rightnode!=NULL)
    {
        get_rect_head_end(node_head->rightnode,node_end,lefttopx,lefttopy,rightbottomx,rightbottomy);
    }

    if(node_head->nextnode!=NULL)
    {
        get_rect_head_end(node_head->nextnode,node_end,lefttopx,lefttopy,rightbottomx,rightbottomy);
    }
}

