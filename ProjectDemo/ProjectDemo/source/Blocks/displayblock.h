#ifndef DISPLAYBLOCK_H
#define DISPLAYBLOCK_H

#include "../Blocks/baseblock.h"
class DisplayBlock : public BaseBlock
{
public:
    DisplayBlock(QString iconPath, int m_pID);
    ~DisplayBlock();

    virtual void save_node(QDomElement &self,QDomDocument &doc) override;
    virtual void read_node(QDomElement &self,QDomDocument &doc) override;
    virtual BaseBlock* clone() override;
    virtual QString GetCode() override;
    void SetInit(QString iconstr, QString tip, QGraphicsView *pView, int x, int y, qreal real);
    void setMyText(const QString &text);
private:
    QGraphicsTextItem m_iShowText;
};

#endif // DISPLAYBLOCK_H
