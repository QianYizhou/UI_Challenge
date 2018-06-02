#include "positionexamine.h"
#include <QApplication>
#include <QScreen>
#include "../define.h"
extern float g_fScale;
extern qreal g_fScaleX;
extern qreal g_fScaleY;
PositionExamine::PositionExamine(QString fileName, int ID, int type)
    :BaseBlock(fileName,ID,type)
{
    setAcceptTouchEvents(true);


}

PositionExamine::PositionExamine(const PositionExamine &other)
    :BaseBlock(other.pixmapPath,other.ID, other.blockType)
{

}

PositionExamine::~PositionExamine()
{
    qDebug("Camera_m::~Camera_m()");

}

BaseBlock* PositionExamine::clone()
{
    PositionExamine* pt = new PositionExamine(*this);
    return pt;
}

void PositionExamine::save_node(QDomElement &self,QDomDocument &doc)
{

}

void PositionExamine::read_node(QDomElement &self,QDomDocument &doc)
{

}

QString PositionExamine::GetCode()
{
    return QString("PositionExamine();");
}
