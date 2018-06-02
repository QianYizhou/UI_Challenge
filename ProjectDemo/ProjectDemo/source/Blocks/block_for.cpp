#include "block_for.h"
#include <math.h>
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int BLOCK_PER_DISTANCE;
int Block_For::forNum = 0;

void Block_For::RefreshValue()
{
}



QString Block_For::GetCode()
{
//    qDebug("m_nLoopTimes = %d", m_nLoopTimes);
    qDebug("Block_For::forNum = %d", Block_For::forNum);
    qDebug("var_a = %d", var_a);
    QString code = "";
    if (false == m_bForeverLoop)
    {
        QString str = "a_" + QString::number(var_a);
        code = "int " + str + "=0;\n";
        code += "for(" + str + "= 0;" + str + " < ";
        code += QString::number(m_nLoopTimes);
        code += ";" + str + "++)\n{\n";
        BaseBlock* node = this->stepNode;
        while (node != NULL)
        {
            code += node->GetCode();
            code += "\n";
            node = node->nextnode;
        }
    }
    else
    {
        code = "while(1)\n{\n";
        BaseBlock* node = this->stepNode;
        while (node != NULL)
        {
            code += node->GetCode();
            code += "\n";
            node = node->nextnode;
        }

    }
    code += "\n}";
    return code;
}

QString Block_For::GetCCode()
{

    qDebug("Block_For::forNum = %d", Block_For::forNum);
    qDebug("var_a = %d", var_a);
    QString code = "";
    if (false == m_bForeverLoop)
    {
        QString str = "a_" + QString::number(var_a);
        code = "int " + str + "=0;\n";
        code += "for(" + str + "= 0;" + str + " < ";
        code += QString::number(m_nLoopTimes);
        code += ";" + str + "++)\n{\n";
        BaseBlock* node = this->stepNode;
        while (node != NULL)
        {
            code += node->GetCCode();
            code += "\n";
            node = node->nextnode;
        }
    }
    else
    {
        code = "while(1)\n{\n";
        BaseBlock* node = this->stepNode;
        while (node != NULL)
        {
            code += node->GetCCode();
            code += "\n";
            node = node->nextnode;
        }

    }
    code += "\n}";
    return code;
}



Block_For::Block_For(QPixmap p,int a)
    :BaseBlock(p,a)
{

    setCacheMode(DeviceCoordinateCache);

    setAcceptHoverEvents(true);

    setAcceptDrops(true);
}

Block_For::Block_For(QString path,int type)
    :BaseBlock(path, BLOCK_FOR, type)
{
    setCacheMode(DeviceCoordinateCache);

    setAcceptHoverEvents(true);

    setAcceptDrops(true);
}

Block_For::Block_For(Block_For& pB)
    :BaseBlock(pB.pixmapPath,pB.ID, pB.blockType)
{
    setCacheMode(pB.cacheMode());
    setAcceptHoverEvents(pB.acceptHoverEvents());
    setAcceptDrops(pB.acceptDrops());


}

BaseBlock* Block_For::clone()
{
    Block_For* pT = new Block_For(*this);

    return pT;
}

QRectF Block_For::GetAllRect()
{
    double leftx = 10000000000.0;
    double lefty = this->pos().y();
    double rightx = -10000000000.0;
    double righty = -10000000000.0;

    this->get_rect_head_end(this,this->nextnode,leftx,lefty,rightx,righty);
    return QRectF(leftx,lefty,fabs(leftx-rightx),fabs(lefty-righty));
}

QRectF Block_For::boundingRect()const
{
    QRectF base = BaseBlock::boundingRect();
    base.setWidth(base.width());
    return base;
}



void Block_For::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseBlock::paint(painter,option, widget);

    return;
}




void Block_For::save_node(QDomElement &self, QDomDocument &doc)
{

}

void Block_For::read_node(QDomElement &self, QDomDocument &doc)
{
    QDomElement child = self.firstChildElement();

   QString val = child.attributeNode("ID").value();
   m_nLoopTimes = val.toInt();

   child = child.nextSiblingElement();
   QString loop = child.attributeNode("ID").value();
   m_bForeverLoop = loop == "true" ? true : false;
}

void Block_For::drawLine()
{
    if (this->stepNode)
        this->stepNode->drawLine();

    BaseBlock::drawLine();


    if (false == next->isVisible())
        next->setVisible(true);
    qreal xLeft = this->x(), yButtom = this->y() + this->boundingRect().height(), xRight = this->x() + this->boundingRect().width();
    int lloop = 1, rloop = 1;
    getRectSize(this->stepNode, xLeft, yButtom, xRight, lloop, rloop);


    bool g_bIpad = false;
    QPointF start_left;
    if(false == g_bIpad)
        start_left.setX(this->pos().x() + 4*g_fScaleX);
    else
        start_left.setX(this->pos().x() + 6*g_fScaleX);
    if(false == g_bIpad)
        start_left.setY(this->pos().y() + this->boundingRect().height()/2 -8*g_fScaleY);
    else
        start_left.setY(this->pos().y() + this->boundingRect().height()/2 -10*g_fScaleY);

    QPointF start_right;
    if(false == g_bIpad)
        start_right.setX(this->pos().x()+this->boundingRect().width() - 4*g_fScaleX);
    else
        start_right.setX(this->pos().x()+this->boundingRect().width() - 8*g_fScaleX);
    if(false == g_bIpad)
        start_right.setY(this->pos().y()+this->boundingRect().height()/2 - 8*g_fScaleY);
    else
        start_right.setY(this->pos().y()+this->boundingRect().height()/2 - 10*g_fScaleY);

    if (this->cubline_left != NULL)
    {
        QPainterPath path;
        path.moveTo(this->x() + this->boundingRect().width()/2,
                    this->y() + this->boundingRect().height() - 26*g_fScaleY);

        path.lineTo(path.currentPosition().x(), path.currentPosition().y() + BLOCK_PER_DISTANCE + 26*g_fScaleY);
        path.moveTo(path.currentPosition().x(), yButtom);
        path.lineTo(path.currentPosition().x(), yButtom + BLOCK_PER_DISTANCE);
        path.lineTo(xLeft - 20, path.currentPosition().y());
        path.lineTo(path.currentPosition().x(), start_left.y());
        path.lineTo(start_left.x(), path.currentPosition().y());

        this->cubline_left->setPath(path);
    }

    if (this->cubline_right != NULL)
    {
        QPainterPath path(start_right);
        path.lineTo(xRight + 20, path.currentPosition().y());
        path.lineTo(path.currentPosition().x(),
                    yButtom + BLOCK_PER_DISTANCE + 20);
        path.lineTo(this->x() + this->boundingRect().width()/2,
                    path.currentPosition().y());
        this->cubline_right->setPath(path);
    }


    qreal prevX = this->next->x();
    qreal prevY = this->next->y();
    this->next->setY(this->mapFromScene(this->cubline_right->path().currentPosition()).y());


    qreal Xoffset,Yoffset;
    Xoffset = this->next->x() - prevX;
    Yoffset = this->next->y() - prevY;
    //TODO
    if (this->nextnode != NULL)
    {
        this->nextnode->setPos(this->nextnode->pos().x() + Xoffset,
                               this->nextnode->pos().y() + Yoffset);
        this->nextnode->updateConnectNode(Xoffset, Yoffset);
    }
    else
    {
        this->cubline->setVisible(false);
    }


//    if (this->stepNode)
//        this->stepNode->drawLine();

    BaseBlock::drawLine();
}

void Block_For::SetInit(QString iconpath, QString tip, QGraphicsView *p_pProjectView, int x, int y, qreal real)
{
    BaseBlock::SetInit(iconpath,tip, p_pProjectView, x, y, real);
    QColor ccc = QColor(22,159,211);
    QPen penline(ccc, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QPainterPath ppath(QPointF(0,0));
    cubline_left = new PerCubeLine(ppath);
    cubline_left->setPen(penline);
    cubline_left->setVisible(true);
    //cubline_left->setToolTip("CUBLINE");
    cubline_left->setZValue(-10);

    cubline_right = new PerCubeLine(ppath);
    cubline_right->setPen(penline);
    cubline_right->setVisible(true);
    //cubline_right->setToolTip("CUBLINE");
    cubline_right->setZValue(-10);

    nextStep = new ConnectBlock(NEXTSTEP);
    nextStep->setParentItem(this);
    nextStep->setToolTip("NEXTSTEP");
    nextStep->setPos(this->boundingRect().width()/2 - nextStep->boundingRect().width()/2,
                     this->boundingRect().height() - 26*g_fScaleY);

    next->setPos(this->boundingRect().width()/2 - next->boundingRect().width()/2,
                     this->boundingRect().height() - 26*g_fScaleY + BLOCK_PER_DISTANCE);
    next->setVisible(false);


    stepNode = NULL;

    p_pProjectView->scene()->addItem(this->cubline_left);
    p_pProjectView->scene()->addItem(this->cubline_right);

    drawLine();
}

void Block_For::updateChildPos()
{
    if (this->nextnode != NULL)
    {
        this->nextnode->setPos(this->x(),
                             this->y() + this->next->y() + BLOCK_PER_DISTANCE);
        this->nextnode->updateChildPos();
    }

    if (this->stepNode != NULL)
    {
        this->stepNode->setPos(this->x(),
                             this->y() + this->boundingRect().height() + BLOCK_PER_DISTANCE);
        this->stepNode->updateChildPos();
    }
}

Block_For::~Block_For()
{
//    if (this->cubline_left)
//        delete this->cubline_left;
//    if (this->cubline_right)
//        delete this->cubline_right;
//    delete m_Ytext;
//    delete m_Ntext;
}

QSize Block_For::getWidgetSize()
{
    if(m_Dialog!=NULL){
        return m_Dialog->m_widget->size();
    }
    return QSize(0, 0);
}

void Block_For::onParamChanged(bool bloop, int loopTimes)
{
    qDebug("onParamChanged    m_nLoopTimes = %d", m_nLoopTimes);
    m_bForeverLoop = bloop;
    m_nLoopTimes = loopTimes;
    qDebug("onParamChanged    m_nLoopTimes = %d", m_nLoopTimes);


    qDebug("m_bForeverLoop    m_bForeverLoop = %d", m_bForeverLoop);
    if(m_bForeverLoop){
        m_count->setMyPixmap(":/res/ios/images/icon_while.png");
    }else{
        m_count->setMyPixmap(":/res/ios/images/icon_for.png");
    }
}
