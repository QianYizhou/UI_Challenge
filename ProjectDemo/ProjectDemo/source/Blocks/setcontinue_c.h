#ifndef SETCONTINUE_C_H
#define SETCONTINUE_C_H

#include "baseblock.h"
#include "blockproperty.h"

class SetContinue_C : public BaseBlock
{
    Q_OBJECT
public:
    SetContinue_C(QString fileName,int ID,int type);
    SetContinue_C(const SetContinue_C &other);
    ~SetContinue_C();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:
//    QGraphicsPixmapItem *m_display;//属性 icon
    QGraphicsTextItem* m_blockText;

};

#endif // SETCONTINUE_C_H
