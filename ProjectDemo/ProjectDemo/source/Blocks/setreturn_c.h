#ifndef SETRETURN_C_H
#define SETRETURN_C_H

#include "baseblock.h"
#include "blockproperty.h"

class SetReturn_C : public BaseBlock
{
    Q_OBJECT
public:
    SetReturn_C(QString fileName,int ID,int type);
    SetReturn_C(const SetReturn_C &other);
    ~SetReturn_C();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:
    //    QGraphicsPixmapItem *m_display;//属性 icon
    QGraphicsTextItem* m_blockText;


};

#endif // SETRETURN_C_H
