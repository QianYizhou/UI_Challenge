#include "block_while.h"
#include "../util/myfont.h"
#include <math.h>

extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
extern int BLOCK_PER_DISTANCE;
void Block_While::RefreshValue()
{
}



QString Block_While::GetCode()
{
    QString code = "while(" + whileString + ")\n{\n";

    if (this->stepNode != NULL)
    {
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

QString Block_While::GetCCode()
{
    QString code = "while(" + whileString + ")\n{\n";

    if (this->stepNode != NULL)
    {
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



Block_While::Block_While(QPixmap p,int a)
    :BaseBlock(p,a)
{

    setCacheMode(DeviceCoordinateCache);

    setAcceptHoverEvents(true);

    setAcceptDrops(true);
}

Block_While::Block_While(QString path,int type)
    :BaseBlock(path, BLOCK_WHILE, type)
{
    setCacheMode(DeviceCoordinateCache);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);

    showconnect = false;

//    m_Ytext = new QGraphicsTextItem(tr("Y"));
//    m_Ytext->setFont(MyFont::getfont(10));
//    m_Ytext->setDefaultTextColor(QColor(255,255,255));
//    m_Ytext->setParentItem(this);

//    if (false == g_bIpad)
//        m_Ytext->setPos((this->boundingRect().width() - m_Ytext->boundingRect().width())/2,
//                        this->boundingRect().height() - m_Ytext->boundingRect().height() - 5*g_fScaleY);
//    else
//        m_Ytext->setPos((this->boundingRect().width() - m_Ytext->boundingRect().width())/2,
//                        this->boundingRect().height() - m_Ytext->boundingRect().height() - 10*g_fScaleY);

    m_condition = new QGraphicsTextItem(tr("循环判断"));
    m_condition->setFont(MyFont::getfont_normal(10));
    m_condition->setDefaultTextColor(QColor(37,37,40));
    m_condition->setTextWidth(100);
    QString html =QString("<div align='center' top =50% >")+m_condition->toPlainText()+QString("</div>");
    m_condition->setHtml(html);
    m_condition->setParentItem(this);
    m_condition->setPos((this->boundingRect().width() - m_condition->boundingRect().width())/2,
                        (this->boundingRect().height()-m_condition->boundingRect().height())/2 - 35* g_fScaleY);

}

Block_While::Block_While(Block_While& pB)
    :BaseBlock(pB.pixmapPath,pB.ID, pB.blockType)
{
    setCacheMode(pB.cacheMode());
    setAcceptHoverEvents(pB.acceptHoverEvents());
    setAcceptDrops(pB.acceptDrops());

    showconnect = pB.showconnect;

    m_condition = new QGraphicsTextItem(tr("循环判断"));
    m_condition->setFont(MyFont::getfont_normal(10));
    m_condition->setDefaultTextColor(QColor(37,37,40));
    m_condition->setTextWidth(100);
    QString html =QString("<div align='center' top =50% >")+m_condition->toPlainText()+QString("</div>");
    m_condition->setHtml(html);
    m_condition->setParentItem(this);
    m_condition->setPos((this->boundingRect().width() - m_condition->boundingRect().width())/2,
                        (this->boundingRect().height()-m_condition->boundingRect().height())/2 - 35* g_fScaleY);
}

Block_While::~Block_While()
{
}

BaseBlock* Block_While::clone()
{
    Block_While* pT = new Block_While(*this);

    return pT;
}

QRectF Block_While::GetAllRect()
{
    double leftx = 10000000000.0;
    int lefty = this->pos().y();
    double rightx = -10000000000.0;
    double righty = -10000000000.0;

    return QRectF(leftx,lefty,fabs(leftx-rightx),fabs(lefty-righty));
}

QRectF Block_While::boundingRect()const
{
    QRectF base = BaseBlock::boundingRect();
    base.setWidth(base.width());
    return base;
}



void Block_While::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseBlock::paint(painter,option, widget);

    return;
}


void Block_While::save_node(QDomElement &self, QDomDocument &doc)
{
}

void Block_While::read_node(QDomElement &self, QDomDocument &doc)
{
    QDomElement child = self.firstChildElement();
    whileString = child.attributeNode("ID").value();

}

void Block_While::drawLine()
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


//    qDebug("next->y() = %f", next->y());
    qreal prevX = this->next->x();
    qreal prevY = this->next->y();
    this->next->setY(this->mapFromScene(this->cubline_right->path().currentPosition()).y());


    qreal Xoffset,Yoffset;
    Xoffset = this->next->x() - prevX;
    Yoffset = this->next->y() - prevY;
    //TODO
    if (this->nextnode != NULL)
    {
        qDebug("Xoffset = %f, Yoffset = %f", Xoffset, Yoffset);
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

void Block_While::SetInit(QString iconpath, QString tip, QGraphicsView *p_pProjectView, int x, int y, qreal real)
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

void Block_While::updateChildPos()
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

QSize Block_While::getWidgetSize()
{
    return QSize(0, 0);
}

void Block_While::onParamChanged(QString str)
{
    if (str.contains("&&&&"))
        str.replace("&&&&", "&&");

    whileString = str;
    qDebug()<<"m_condition->toPlainText() = "<<m_condition->toPlainText();
    if(whileString.contains("&&")){
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText("&&");
    }else if(whileString.contains("||")){
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText("||");
    }else if((whileString.size() > 4)){
        m_condition->setFont(MyFont::getfont_normal(8));
        m_condition->setPlainText(whileString);
    }else{
        whileString="1";
        m_condition->setFont(MyFont::getfont_normal(10));
        m_condition->setPlainText(tr("循环判断"));
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
