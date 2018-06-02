#include "block_if.h"
#include <math.h>
#include "../util/myfont.h"
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int BLOCK_PER_DISTANCE;
void Block_If::RefreshValue()
{
}



QString Block_If::GetCode()
{
    QString code = "if(" + ifString + ")\n{\n";
    BaseBlock* node = this->leftnode;

    //if
    while(node != NULL)
    {
        code += node->GetCode();
		code += "\n";
        node = node->nextnode;
    }

    if (this->rightnode != NULL)
    {
        code += "\n}\nelse\n{\n";
        //else
        node = this->rightnode;
        while(node != NULL)
        {
            code += node->GetCode();
            code += "\n";
            node = node->nextnode;
        }
    }

    code += "\n}";
    return code;
}

QString Block_If::GetCCode()
{
    QString code = "if(" + ifString + ")\n{\n";
    BaseBlock* node = this->leftnode;

    //if
    while(node != NULL)
    {
        code += node->GetCCode();
        code += "\n";
        node = node->nextnode;
    }

    if (this->rightnode != NULL)
    {
        code += "\n}\nelse\n{\n";
        //else
        node = this->rightnode;
        while(node != NULL)
        {
            code += node->GetCCode();
            code += "\n";
            node = node->nextnode;
        }
    }

    code += "\n}";
    return code;
}



Block_If::Block_If(QPixmap p,int a)
    :BaseBlock(p,a)
    , m_Ytext(NULL)
    , m_Ntext(NULL)
    , m_Dialog(NULL)
{

    setCacheMode(DeviceCoordinateCache);

    setAcceptHoverEvents(true);

    setAcceptDrops(true);
}

Block_If::Block_If(QString path,int type)
    :BaseBlock(path, BLOCK_IF, type)
    , m_Ytext(NULL)
    , m_Ntext(NULL)
    , m_Dialog(NULL)
{
    setCacheMode(DeviceCoordinateCache);

    setAcceptHoverEvents(true);

    setAcceptDrops(true);

    showconnect = false;

    left = new ConnectBlock(LEFT);
    left->setParentItem(this);
    left->setToolTip("LEFT");
    left->setPos(-left->boundingRect().width() + 10,
                 this->boundingRect().height()/2 - left->boundingRect().height()/2 + 10);

    right = new ConnectBlock(RIGHT);
    right->setParentItem(this);
    right->setToolTip("RIGHT");
    right->setPos(this->boundingRect().width() - 10,
                  this->boundingRect().height()/2 - right->boundingRect().height()/2 + 10);

//    m_Ytext = new QGraphicsTextItem(tr("Y"));
//    m_Ytext->setFont(MyFont::getfont(10));
//    m_Ytext->setDefaultTextColor(QColor(255,255,255));
//    m_Ytext->setParentItem(this);
//    m_Ytext->setPos(62*g_fScaleX,this->boundingRect().height()/2 - 38*g_fScaleY);

    m_condition = new QGraphicsTextItem(tr("条件判断"));
    m_condition->setFont(MyFont::getfont_normal(10));
    m_condition->setDefaultTextColor(QColor(37,37,40));
    m_condition->setTextWidth(100);
    QString html =QString("<div align='center' top =50% >")+m_condition->toPlainText()+QString("</div>");
    m_condition->setHtml(html);
    m_condition->setParentItem(this);
    m_condition->setPos((this->boundingRect().width() - m_condition->boundingRect().width())/2,
                        (this->boundingRect().height()-m_condition->boundingRect().height())/2 - 25* g_fScaleY);

    ifString = "1";
}

Block_If::Block_If(Block_If& pB)
    :BaseBlock(pB.pixmapPath,pB.ID, pB.blockType)
{
    setCacheMode(pB.cacheMode());
    setAcceptHoverEvents(pB.acceptHoverEvents());
    setAcceptDrops(pB.acceptDrops());

    showconnect = pB.showconnect;

    left = new ConnectBlock(LEFT);
    left->setParentItem(this);
    left->setToolTip("LEFT");
    left->setPos(-left->boundingRect().width() + 10,
                 this->boundingRect().height()/2 - left->boundingRect().height()/2 + 10);

    right = new ConnectBlock(RIGHT);
    right->setParentItem(this);
    right->setToolTip("RIGHT");
    right->setPos(this->boundingRect().width() - 10,
                  this->boundingRect().height()/2 - right->boundingRect().height()/2 + 10);

//    m_Ytext = new QGraphicsTextItem(tr("Y"));
//    m_Ytext->setFont(MyFont::getfont(12));
//    m_Ytext->setDefaultTextColor(QColor(255,255,255));
//    m_Ytext->setParentItem(this);
//    m_Ytext->setPos(62*g_fScaleX,this->boundingRect().height()/2 - 37*g_fScaleY);

    m_condition = new QGraphicsTextItem(tr("条件判断"));
    m_condition->setFont(MyFont::getfont_normal(10));
    m_condition->setDefaultTextColor(QColor(37,37,40));
    m_condition->setTextWidth(100);
    QString html =QString("<div align='center' top =50% >")+m_condition->toPlainText()+QString("</div>");
    m_condition->setHtml(html);
    m_condition->setParentItem(this);
    m_condition->setPos((this->boundingRect().width() - m_condition->boundingRect().width())/2,
                        (this->boundingRect().height()-m_condition->boundingRect().height())/2 - 25* g_fScaleY);


}

Block_If::~Block_If()
{
//    if (this->cubline_left)
//    {
//        delete this->cubline_left;
//        this->cubline_left = NULL;
//    }
//    if (this->cubline_right)
//    {
//        delete this->cubline_right;
//        this->cubline_right = NULL;
//    }
////    if (this->leftnode)
////        delete this->leftnode;
////    if (this->rightnode)
////        delete this->rightnode;
//    delete m_Ytext;
//    delete m_Ntext;
    if(m_Dialog!=NULL){
        delete m_Dialog;
        m_Dialog = NULL;
    }
}

BaseBlock* Block_If::clone()
{
    Block_If* pT = new Block_If(*this);

    return pT;
}

QRectF Block_If::GetAllRect()
{
    double leftx = 10000000000.0;
    int lefty = this->pos().y();
    double rightx = -10000000000.0;
    double righty = -10000000000.0;

    return QRectF(leftx,lefty,fabs(leftx-rightx),fabs(lefty-righty));
}

QRectF Block_If::boundingRect()const
{
    QRectF base = BaseBlock::boundingRect();
    base.setWidth(base.width());
    return base;
}



void Block_If::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseBlock::paint(painter,option, widget);

    return;
}




void Block_If::save_node(QDomElement &self, QDomDocument &doc)
{
}

void Block_If::read_node(QDomElement &self, QDomDocument &doc)
{

}

void Block_If::drawLine()
{
    if (this->leftnode != NULL)
        this->leftnode->drawLine();
    if (this->rightnode != NULL)
        this->rightnode->drawLine();

    if (false == next->isVisible())
        next->setVisible(true);
    BaseBlock *if_left = NULL;
    BaseBlock *if_right = NULL;

    if_left = this->leftnode;
    if (if_left!=NULL)
    {
        while (if_left->nextnode)
        {
            if_left = if_left->nextnode;
        }
    }

    if_right = this->rightnode;
    if (if_right!=NULL)
    {
        while (if_right->nextnode)
        {
            if_right = if_right->nextnode;
        }
    }

    //
    int leftsubnode = 0;
    int rightsubnode = 0;
    if (this->leftnode != NULL)
    {
        rightsubnode = this->get_rightCount();
    }
    if (this->rightnode != NULL)
    {
        leftsubnode = this->get_leftCount();
    }

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

    //CASE 1:
    if (if_left==NULL && if_right!=NULL)
    {
        //QPointF point = if_right->y() + if_right->next->y();//if_right->next->mapToScene(if_right->next->x(), if_right->next->y());
        qreal rightdis = if_right->y() + if_right->next->y();

        if (this->cubline_left!=NULL)
        {
            QPainterPath path(QPointF(0,0));

            path.moveTo(start_left);
//            path.lineTo(start_left.x() - leftsubnode*BLOCK_PER_DISTANCE,start_left.y());
            path.lineTo(path.currentPosition().x(),
                        rightdis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());

            this->cubline_left->setPath(path);
            this->cubline_left->setVisible(true);
            this->cubline_left->update();
        }

        if (this->cubline_right!=NULL)
        {
            QPainterPath path(QPointF(0,0));

            path.moveTo(start_right);

            path.lineTo(this->rightnode->x() + this->rightnode->boundingRect().width()/2
                        , path.currentPosition().y());
            path.lineTo(path.currentPosition().x() ,this->rightnode->y());

//            path.moveTo(if_right->pos().x() + if_right->boundingRect().width()/2,
//                        if_right->pos().y() + if_right->boundingRect().height() - 10);

            path.moveTo(path.currentPosition().x(), if_right->y() + if_right->next->y());
            path.lineTo(path.currentPosition().x(), rightdis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());

            this->cubline_right->setPath(path);
            this->cubline_right->setVisible(true);
            this->cubline_right->update();
        }
    }


    //CASE 2:
    if(if_right==NULL&&if_left!=NULL)
    {

        //QPointF point = if_left->y() + if_left->next->y();//if_left->next->mapToScene(if_left->next->x(), if_left->next->y());
        qreal leftdis = if_left->y() + if_left->next->y();// + if_left->boundingRect().height();
        //qDebug("if_left->next->y() = %f", if_left->next->y());
        if(this->cubline_left!=NULL)
        {
            QPainterPath path(QPointF(0,0));

            path.moveTo(start_left);

            path.lineTo(this->leftnode->x() + this->leftnode->boundingRect().width()/2,
                        path.currentPosition().y());
            path.lineTo(path.currentPosition().x(),
                        this->leftnode->pos().y());
//            path.moveTo(if_left->x() + if_left->boundingRect().width()/2,
//                        if_left->y() + if_left->boundingRect().height() - 10);
            path.moveTo(path.currentPosition().x(), if_left->y() + if_left->next->y());
            path.lineTo(path.currentPosition().x(), leftdis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());

            this->cubline_left->setPath(path);
            this->cubline_left->setVisible(true);
            this->cubline_left->update();

        }

        if (this->cubline_right!=NULL)
        {
            QPainterPath path(QPointF(0,0));
            path.moveTo(start_right);

//            path.lineTo(path.currentPosition().x() + rightsubnode*BLOCK_PER_DISTANCE
//                        , path.currentPosition().y());
            path.lineTo(path.currentPosition().x() ,
                        leftdis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2, path.currentPosition().y());


            this->cubline_right->setPath(path);
            this->cubline_right->setVisible(true);
            this->cubline_right->update();

        }
    }

    //CASE 3:
    if(if_left!=NULL&&if_right!=NULL)
    {
        qreal leftdis = if_left->y() + if_left->next->y();//if_left->boundingRect().height();
        qreal rightdis = if_right->y() + if_right->next->y();//if_right->boundingRect().height();
        qreal ydis = leftdis > rightdis ? leftdis : rightdis ;

        if (this->cubline_left != NULL)
        {
            QPainterPath path(QPointF(0,0));

            path.moveTo(start_left);
            path.lineTo(this->leftnode->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());
            path.lineTo(path.currentPosition().x(),
                        this->leftnode->y());
//            path.moveTo(if_left->x() + if_left->boundingRect().width()/2,
//                        if_left->y() + if_left->boundingRect().height() - 10);
            path.moveTo(path.currentPosition().x(), if_left->y() + if_left->next->y());
            path.lineTo(path.currentPosition().x(),
                        ydis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());


            this->cubline_left->setPath(path);
            this->cubline_left->setVisible(true);
            this->cubline_left->update();

        }


        if (this->cubline_right!=NULL)
        {
            QPainterPath path(QPointF(0,0));

            path.moveTo(start_right);

            path.lineTo(this->rightnode->x() + this->rightnode->boundingRect().width()/2,
                        path.currentPosition().y());
            path.lineTo(path.currentPosition().x(),
                        this->rightnode->y());
//            path.moveTo(if_right->x() + if_right->boundingRect().width()/2,
//                        if_right->y() + if_right->boundingRect().height() - 10);
            path.moveTo(path.currentPosition().x(), if_right->y() + if_right->next->y());
            path.lineTo(path.currentPosition().x(),
                        ydis + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());

            this->cubline_right->setPath(path);
            this->cubline_right->setVisible(true);
            this->cubline_right->update();

        }
    }


    //CASE 4:
    if (if_left==NULL&&if_right==NULL)
    {
        if (this->cubline_left!=NULL)
        {
            QPainterPath path(start_left);
//            path.lineTo(path.currentPosition().x() - leftsubnode*BLOCK_PER_DISTANCE,
//                        path.currentPosition().y());
            path.lineTo(path.currentPosition().x(),
                        path.currentPosition().y() + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());
            this->cubline_left->setPath(path);
            this->cubline_left->setVisible(true);
            this->cubline_left->update();

        }

        if (this->cubline_right!=NULL)
        {
            QPainterPath path(start_right);
//            path.lineTo(path.currentPosition().x() + rightsubnode*BLOCK_PER_DISTANCE,
//                        path.currentPosition().y());
            path.lineTo(path.currentPosition().x(),
                        path.currentPosition().y() + BLOCK_PER_DISTANCE);
            path.lineTo(this->x() + this->boundingRect().width()/2,
                        path.currentPosition().y());

            this->cubline_right->setPath(path);
            this->cubline_right->setVisible(true);
            this->cubline_right->update();

        }
    }

//    QPointF relative = this->cubline_left->path().currentPosition();

    qreal prevX = this->next->x();
    qreal prevY = this->next->y();
    this->next->setY(this->mapFromScene(this->cubline_left->path().currentPosition()).y());


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

//    if (this->leftnode != NULL)
//        this->leftnode->drawLine();
//    if (this->rightnode != NULL)
//        this->rightnode->drawLine();

    BaseBlock::drawLine();
}

void Block_If::SetInit(QString iconpath, QString tip, QGraphicsView *p_pProjectView, int x, int y, qreal real)
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

    p_pProjectView->scene()->addItem(this->cubline_left);
    p_pProjectView->scene()->addItem(this->cubline_right);

    next->setVisible(false);

    drawLine();
}

void Block_If::get_last(BaseBlock *node,int &disy,int &disx)
{

    if(node==NULL)
        return;


    if(node->pos().y()>disy)
    {
        disy = node->pos().y() + node->boundingRect().height();
        disx = node->pos().x() + node->boundingRect().width()/2;
    }


    if(node->leftnode!=NULL)
    {
        get_last(node->leftnode,disy,disx);
    }

    if(node->rightnode!=NULL)
    {
        get_last(node->rightnode,disy,disx);
    }

    if(node->nextnode!=NULL)
    {
        get_last(node->nextnode,disy,disx);
    }


}

void Block_If::updateNodePos()
{
//    int lcount = this->get_leftCount();
//    int rcount = this->get_rightCount();

//    if (this->leftnode != NULL)
//    {
//        this->leftnode->setPos(this->x() - rcount*(this->boundingRect().width()/2), this->y() + this->boundingRect().height());
//        this->leftnode->updateNodePos();
//    }

//    if (this->rightnode != NULL)
//    {
//        this->rightnode->setPos(this->x() + lcount*(this->boundingRect().width()/2), this->y() + this->boundingRect().height());
//        this->rightnode->updateNodePos();
//    }
    BaseBlock::updateNodePos();

}

void Block_If::updateChildPos()
{
//    int lcount = this->get_leftCount();
//    int rcount = this->get_rightCount();
    //qDebug("lcount = %d, rcount = %d", lcount, rcount);

    if (this->leftnode != NULL)
    {
        this->leftnode->updateChildPos();
        qreal xLeft = this->leftnode->x();
        qreal xRight = this->leftnode->x() + this->leftnode->boundingRect().width();
        qreal yButtom = this->leftnode->y() + this->leftnode->boundingRect().height();
        int lloop = 1, rloop = 1;
        getRectSize(this->leftnode, xLeft, yButtom, xRight, lloop, rloop);

        qreal offset = xRight - (this->leftnode->x() + this->leftnode->boundingRect().width()) + this->leftnode->boundingRect().width()/2 + 26;

        this->leftnode->setPos(this->x() - offset, this->y() + this->boundingRect().height());
        this->leftnode->updateChildPos();
    }

    if (this->rightnode != NULL)
    {
        this->rightnode->updateChildPos();
        qreal xLeft = this->rightnode->x();
        qreal xRight = this->rightnode->x() + this->rightnode->boundingRect().width();
        qreal yButtom = this->rightnode->y() + this->rightnode->boundingRect().height();
        int lloop = 1, rloop = 1;
        getRectSize(this->rightnode, xLeft, xRight, yButtom, lloop, rloop);

        qreal offset = this->rightnode->x() - xLeft + this->rightnode->boundingRect().width()/2 + 26;

        this->rightnode->setPos(this->x() + offset, this->y() + this->boundingRect().height());
        this->rightnode->updateChildPos();
    }

    if (this->leftnode != NULL || this->rightnode != NULL)
    {
        BaseBlock *if_left = NULL;
        BaseBlock *if_right = NULL;

        if_left = this->leftnode;
        if (if_left!=NULL)
        {
            while (if_left->nextnode)
            {
                if_left = if_left->nextnode;
            }
        }

        if_right = this->rightnode;
        if (if_right!=NULL)
        {
            while (if_right->nextnode)
            {
                if_right = if_right->nextnode;
            }
        }

        qreal leftdis = 0;
        if (if_left)
            leftdis = if_left->y() + if_left->next->y() - this->y();
        qreal rightdis = 0;
        if (if_right)
            rightdis = if_right->y() + if_right->next->y() - this->y();
        qreal ydis = leftdis > rightdis ? leftdis : rightdis ;

        this->next->setY(ydis + BLOCK_PER_DISTANCE);
    }
    else
    {
        this->next->setY(this->boundingRect().width() - 26*g_fScaleY);
    }

    if (this->nextnode != NULL)
    {
        this->nextnode->setPos(this->x(),
                             this->y() + this->next->y() + BLOCK_PER_DISTANCE);
        this->nextnode->updateChildPos();
    }
}

QSize Block_If::getWidgetSize()
{
    if(m_Dialog!=NULL){
        return m_Dialog->m_widget->size();
    }
    return QSize(0, 0);
}

void Block_If::onParamChanged(QString str)
{
    if (str.contains("&&&&"))
        str.replace("&&&&", "&&");

    ifString = str;
    qDebug()<<"ifString = "<<ifString;

    if(ifString.contains("&&")){
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText("&&");
    }else if(ifString.contains("||")){
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText("||");
    }else if((ifString.size() > 4)){
        m_condition->setFont(MyFont::getfont_normal(8));
        m_condition->setPlainText(ifString);
    }else{
        ifString="1";
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText(tr("条件判断"));
    }
    qDebug()<<"m_condition->toPlainText() = "<<m_condition->toPlainText();
    //< &lt; <= &le; > &gt; >= &ge;
    if(m_condition->toPlainText().contains("<")){
        m_condition->setPlainText(m_condition->toPlainText().replace("<","&lt;"));
    }
//    if(m_condition->toPlainText().contains("<=")){
//        m_condition->setPlainText(m_condition->toPlainText().replace("<=","&le;"));
//    }
    if(m_condition->toPlainText().contains(">")){
        m_condition->setPlainText(m_condition->toPlainText().replace(">","&gt;"));
    }
//    if(m_condition->toPlainText().contains(">=")){
//        m_condition->setPlainText(m_condition->toPlainText().replace(">=","&ge;"));
//    }
    qDebug()<<"m_condition->toPlainText() = "<<m_condition->toPlainText();
    QString html =QString("<div align='center' top =50% >")+m_condition->toPlainText()+QString("</div>");
    m_condition->setHtml(html);
}

//void Block_If::updateConnetLine()
//{
//    //更新连接节点的位置
//    if (this->nextnode != NULL)
//    {
//        this->nextnode->updateConnetLine();
//    }

//    if (this->leftnode != NULL)
//    {
//        this->leftnode->updateConnetLine();
//    }

//    if (this->rightnode != NULL)
//    {
//        this->rightnode->updateConnetLine();
//    }

//    this->drawLine();
//}

//void Block_If::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//{
//    BaseBlock::mouseMoveEvent(event);
//    this->drawLine();
//}

//void Block_If::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    BaseBlock::mouseReleaseEvent(event);
//    this->drawLine();
//}

//Block_If_End::Block_If_End(QPixmap p,int a)
//    :BaseBlock(p,a)
//{
//    setCacheMode(DeviceCoordinateCache);
//    setAcceptHoverEvents(true);
//    setAcceptDrops(true);
//}


//Block_If_End::Block_If_End(QString path1,int a)
//    :BaseBlock(path1,a)
//{

//    setCacheMode(DeviceCoordinateCache);
//    setAcceptHoverEvents(true);
//    setAcceptDrops(true);

//    cubline_end = NULL;
//    QPainterPath path(QPointF(0,0));
//    cubline_end = new PerCubeLine(path);

//    cubline_end->setVisible(false);



//    cubline_left = NULL;

//    cubline_left = new PerCubeLine(path);
//    cubline_left->setVisible(false);


//    cubline_right = NULL;

//    cubline_right = new PerCubeLine(path);
//    cubline_right->setVisible(false);


//}


//Block_If_End::Block_If_End(Block_If_End& pB)
//    :BaseBlock(pB.filepath,pB.ID)
//{
//    setCacheMode(pB.cacheMode());
//    setAcceptHoverEvents(pB.acceptHoverEvents());
//    setAcceptDrops(pB.acceptDrops());

//    cubline_end = NULL;
//    QPainterPath path(QPointF(0,0));
//    cubline_end = new PerCubeLine(pB.cubline_end->path());
//    cubline_end->setVisible(pB.cubline_end->isVisible());


//    cubline_left = NULL;
//    cubline_left = new PerCubeLine(pB.cubline_left->path());
//    cubline_left->setVisible(pB.cubline_end->isVisible());

//    cubline_right = NULL;
//    cubline_right = new PerCubeLine(pB.cubline_right->path());
//    cubline_right->setVisible(pB.cubline_end->isVisible());

//}

//BaseBlock* Block_If_End::clone()
//{
//    Block_If_End* pT = new Block_If_End(*this);

//    return pT;
//}


//QRectF Block_If_End::boundingRect()const
//{
//    return QRectF(0,0,300,10);
//}



//void Block_If_End::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    BaseBlock::paint(painter, option, widget);
//}
