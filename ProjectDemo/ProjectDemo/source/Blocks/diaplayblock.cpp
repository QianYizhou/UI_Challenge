#include "displayblock.h"
#include "../util/myfont.h"

DisplayBlock::DisplayBlock(QString iconPath, int m_pID):
    BaseBlock(iconPath,m_pID)
{

}

DisplayBlock::~DisplayBlock()
{

}

void DisplayBlock::SetInit(QString iconstr, QString tip, QGraphicsView *pView, int x, int y, qreal real)
{
    BaseBlock::SetInit(iconstr, tip, pView, x, y, real);

    QPen pen;
    pen.setColor(Qt::white);
    m_iShowText.setTextWidth(this->boundingRect().width() - 80);
    QString html =QString("<div align='center' top =50% >")+getMyText()+QString("</div>");
    m_iShowText.setHtml(html);
    m_iShowText.setFont(MyFont::getfont_normal(12));
    m_iShowText.setParentItem(this);
    m_iShowText.setDefaultTextColor(QColor(255,255,255));
    m_iShowText.setPos(40,(this->boundingRect().height() - m_iShowText.boundingRect().height())/2 - 10);
}

void DisplayBlock::setMyText(const QString &text)
{
    BaseBlock::setMyText(text);
    QString html =QString("<div align='center' top =50% >")+text+QString("</div>");
    m_iShowText.setHtml(html);
    update();
}

void DisplayBlock::save_node(QDomElement &self, QDomDocument &doc)
{

}

void DisplayBlock::read_node(QDomElement &self, QDomDocument &doc)
{

}

BaseBlock *DisplayBlock::clone()
{

}

QString DisplayBlock::GetCode()
{

}
