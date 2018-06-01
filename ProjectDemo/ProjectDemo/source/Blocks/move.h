#ifndef MOVE_H
#define MOVE_H

#include "baseblock.h"
#include "blockproperty.h"
class Move : public BaseBlock
{
    Q_OBJECT
public:
    Move(QString fileName, int ID, int type);
    Move(const Move &other);
    ~Move();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:

};

#endif // MOVE_H
