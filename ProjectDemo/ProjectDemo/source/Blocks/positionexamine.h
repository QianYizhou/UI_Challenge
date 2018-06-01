#ifndef POSITIONEXAMINE_H
#define POSITIONEXAMINE_H

#include "baseblock.h"
#include "blockproperty.h"
class PositionExamine : public BaseBlock
{
    Q_OBJECT
public:
    PositionExamine(QString fileName, int ID, int type);
    PositionExamine(const PositionExamine &other);
    ~PositionExamine();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:

};

#endif // POSITIONEXAMINE_H
