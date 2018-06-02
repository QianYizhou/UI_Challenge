#ifndef GRAB_H
#define GRAB_H

#include "baseblock.h"
#include "blockproperty.h"
class Grab : public BaseBlock
{
    Q_OBJECT
public:
    Grab(QString fileName, int ID, int type);
    Grab(const Grab &other);
    ~Grab();
    BaseBlock* clone();

    void save_node(QDomElement &self,QDomDocument &doc);
    void read_node(QDomElement &self,QDomDocument &doc);
    QString GetCode();

private:

};

#endif // GRAB_H
