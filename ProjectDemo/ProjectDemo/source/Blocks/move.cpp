#include "move.h"
#include <QApplication>
#include <QScreen>
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
Move::Move(QString fileName, int ID, int type)
    :BaseBlock(fileName,ID,type)
{
    setAcceptTouchEvents(true);

}

Move::Move(const Move &other)
    :BaseBlock(other.pixmapPath,other.ID, other.blockType)
{
    setAcceptTouchEvents(true);

}

Move::~Move()
{
    qDebug("Move::~Move()");
}

BaseBlock* Move::clone()
{
    Move* pt = new Move(*this);
    return pt;
}

void Move::save_node(QDomElement &self,QDomDocument &doc)
{

}

void Move::read_node(QDomElement &self,QDomDocument &doc)
{

}

QString Move::GetCode()
{
    return QString("Move();");
}
