#include "grab.h"
#include <QApplication>
#include <QScreen>
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
Grab::Grab(QString fileName, int ID, int type)
    :BaseBlock(fileName,ID,type)
{
    setAcceptTouchEvents(true);

}

Grab::Grab(const Grab &other)
    :BaseBlock(other.pixmapPath,other.ID, other.blockType)
{
    setAcceptTouchEvents(true);

}

Grab::~Grab()
{
    qDebug("Grab::~Grab()");
}

BaseBlock* Grab::clone()
{
    Grab* pt = new Grab(*this);
    return pt;
}

void Grab::save_node(QDomElement &self,QDomDocument &doc)
{

}

void Grab::read_node(QDomElement &self,QDomDocument &doc)
{

}

QString Grab::GetCode()
{
    return QString("Grab();");
}
