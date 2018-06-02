#ifndef SETBUREAK_C_H
#define SETBUREAK_C_H

#include "baseblock.h"
#include "blockproperty.h"
class SetBreak_C : public BaseBlock
{
    Q_OBJECT
public:
    SetBreak_C(QString fileName,int ID,int type);
    SetBreak_C(const SetBreak_C &other);
    ~SetBreak_C();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:
//    QGraphicsPixmapItem *m_display;//属性 icon
    QGraphicsTextItem* m_blockText;


};

#endif // SETBUREAK_C_H
