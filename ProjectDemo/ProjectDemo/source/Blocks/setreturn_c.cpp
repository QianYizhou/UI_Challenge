#include "setreturn_c.h"
#include "../util/myfont.h"
#include <QScreen>

extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;

SetReturn_C::SetReturn_C(QString fileName, int ID, int type)
    :BaseBlock(fileName,ID,type)
    , m_blockText(NULL)
{
    setAcceptTouchEvents(true);

    m_blockText = new QGraphicsTextItem();
    m_blockText->setPlainText(tr("Return"));
    m_blockText->setFont(MyFont::getfont_normal(12));
    m_blockText->setDefaultTextColor(QColor(37,37,40));
    m_blockText->setTextWidth(120);
    QString html =QString("<div align='center' top =50% >")+m_blockText->toPlainText()+QString("</div>");
    m_blockText->setHtml(html);
    m_blockText->setParentItem(this);
    m_blockText->setPos((this->boundingRect().width() - m_blockText->boundingRect().width())/2 + 40* g_fScaleX,
                        (this->boundingRect().height()-m_blockText->boundingRect().height())/2 - 10* g_fScaleY);

}

SetReturn_C::SetReturn_C(const SetReturn_C &other)
    :BaseBlock(other.pixmapPath,other.ID, other.blockType)
{
    setAcceptTouchEvents(true);

    m_blockText = new QGraphicsTextItem();
    m_blockText->setPlainText(tr("Return"));
    m_blockText->setFont(MyFont::getfont_normal(12));
    m_blockText->setDefaultTextColor(QColor(37,37,40));
    m_blockText->setTextWidth(120);
    QString html =QString("<div align='center' top =50% >")+m_blockText->toPlainText()+QString("</div>");
    m_blockText->setHtml(html);
    m_blockText->setParentItem(this);
    m_blockText->setPos((this->boundingRect().width() - m_blockText->boundingRect().width())/2 + 40* g_fScaleX,
                        (this->boundingRect().height()-m_blockText->boundingRect().height())/2 - 10* g_fScaleY);

}

SetReturn_C::~SetReturn_C()
{
    if(m_blockText!=NULL){
        delete m_blockText;
        m_blockText = NULL;
    }
}

BaseBlock* SetReturn_C::clone()
{
    SetReturn_C* pt = new SetReturn_C(*this);
    return pt;
}

void SetReturn_C::save_node(QDomElement &self,QDomDocument &doc)
{

}

void SetReturn_C::read_node(QDomElement &self,QDomDocument &doc)
{

}

QString SetReturn_C::GetCode()
{
    return QString( "return;");
}

