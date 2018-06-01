#ifndef BLOCK_IF_H
#define BLOCK_IF_H

#include <QDebug>

#include "../define.h"
#include <QObject>
#include "baseblock.h"
#include "ifdialog.h"
#include "blockproperty.h"
class Block_If : public BaseBlock
{

    Q_OBJECT

public:
    bool showconnect;
    QString GetCode();
    virtual QString GetCCode();

    void RefreshValue();
    Block_If(QPixmap p,int a);
    Block_If(QString path, int type);
    Block_If(Block_If& pB);
    ~Block_If();
    BaseBlock* clone();
    QRectF GetAllRect();
    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void save_node(QDomElement &self, QDomDocument &doc);

    void read_node(QDomElement &self, QDomDocument &doc);

    virtual void drawLine() override;

    virtual bool alwaysUpdateCubLine() override{return true;}

    void get_last(BaseBlock *node,int &disy,int &disx);

    virtual void SetInit(QString iconpath, QString tip, QGraphicsView* p_pProjectView, int x, int y, qreal real) override;

    virtual void updateNodePos() override;
    virtual void updateChildPos() override;
    virtual QSize getWidgetSize() override;

public slots:
    void onParamChanged(QString);

private:
    QString ifString;

    QGraphicsTextItem* m_Ytext;
    QGraphicsTextItem* m_condition;
    QGraphicsTextItem* m_Ntext;
    IfDialog* m_Dialog;

//protected:
//    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
//    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //virtual void updateConnetLine() override;

};




//class Block_If_End : public BaseBlock
//{
//public:

//    PerCubeLine *cubline_end;

//    PerCubeLine *cubline_left;
//    PerCubeLine *cubline_right;


//    Block_If_End(QPixmap p,int a);

//    Block_If_End(QString path1,int a);


//    Block_If_End(Block_If_End& pB);

//    BaseBlock* clone();

//    QRectF boundingRect()const;

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

//    virtual void save_node(QDomElement &self,QDomDocument &doc){Q_UNUSED(self);Q_UNUSED(doc);}
//    virtual void read_node(QDomElement &self,QDomDocument &doc){Q_UNUSED(self);Q_UNUSED(doc);}
//    virtual QString GetCode(){return "";}
//};

#endif // BLOCK_IF_H
